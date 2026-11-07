// Minimal parser for the YAML subset Unity writes (scenes, prefabs, assets, metas).
'use strict';

function indentOf(s) { let i = 0; while (i < s.length && s[i] === ' ') i++; return i; }

// ---- flow values: {a: b, c: [d, e]} -------------------------------------------------
function parseFlow(s) {
  let i = 0;
  const ws = () => { while (i < s.length && (s[i] === ' ' || s[i] === '\t')) i++; };
  function scalar(stops) {
    ws();
    if (s[i] === "'" || s[i] === '"') return quoted();
    let st = i;
    while (i < s.length && !stops.includes(s[i])) i++;
    return s.slice(st, i).trim();
  }
  function quoted() {
    const q = s[i++]; let out = '';
    while (i < s.length) {
      const c = s[i];
      if (q === "'" && c === "'" && s[i + 1] === "'") { out += "'"; i += 2; continue; }
      if (c === q) { i++; break; }
      if (q === '"' && c === '\\') { out += unescapeOne(s, i); i += escLen(s, i); continue; }
      out += c; i++;
    }
    return out;
  }
  function value(stops) {
    ws();
    if (s[i] === '{') return map();
    if (s[i] === '[') return seq();
    return scalar(stops);
  }
  function map() {
    i++; const o = {};
    for (;;) {
      ws();
      if (s[i] === '}') { i++; return o; }
      let st = i; while (i < s.length && s[i] !== ':' && s[i] !== '}') i++;
      const key = s.slice(st, i).trim();
      if (s[i] === ':') i++;
      o[key] = value([',', '}']);
      ws(); if (s[i] === ',') i++;
      if (i >= s.length) return o;
    }
  }
  function seq() {
    i++; const a = [];
    for (;;) {
      ws();
      if (s[i] === ']') { i++; return a; }
      a.push(value([',', ']']));
      ws(); if (s[i] === ',') i++;
      if (i >= s.length) return a;
    }
  }
  return value([]);
}

function escLen(s, i) {
  const c = s[i + 1];
  if (c === 'x') return 4; if (c === 'u') return 6; if (c === 'U') return 10; return 2;
}
function unescapeOne(s, i) {
  const c = s[i + 1];
  switch (c) {
    case 'n': return '\n'; case 't': return '\t'; case 'r': return '\r'; case '0': return '\0';
    case '"': return '"'; case '\\': return '\\'; case '/': return '/'; case ' ': return ' ';
    case 'x': return String.fromCharCode(parseInt(s.substr(i + 2, 2), 16));
    case 'u': return String.fromCharCode(parseInt(s.substr(i + 2, 4), 16));
    case 'U': return String.fromCodePoint(parseInt(s.substr(i + 2, 8), 16));
    case 'N': return '\u0085'; case '_': return ' '; case 'L': return ' '; case 'P': return ' ';
    default: return c;
  }
}

// Fold continuation lines (YAML line folding: newline -> space, blank line -> \n).
function fold(parts) {
  let out = '';
  for (let k = 0; k < parts.length; k++) {
    const p = parts[k];
    if (k === 0) { out = p; continue; }
    if (p === '') { out += '\n'; continue; }
    if (out.endsWith('\n') || out === '') out += p; else out += ' ' + p;
  }
  return out;
}

function decodeDouble(raw) {
  // raw is the text between the quotes with folding already applied, except escaped line breaks.
  let out = '';
  for (let i = 0; i < raw.length;) {
    if (raw[i] === '\\') { out += unescapeOne(raw, i); i += escLen(raw, i); }
    else out += raw[i++];
  }
  return out;
}

// ---- block structure -----------------------------------------------------------------
class Parser {
  constructor(lines) { this.L = lines; this.i = 0; }
  peek() {
    while (this.i < this.L.length && this.L[this.i].trim() === '') this.i++;
    return this.i < this.L.length ? this.L[this.i] : null;
  }
  block(ind) {
    const l = this.peek();
    if (l === null) return null;
    const li = indentOf(l);
    if (l.slice(li).startsWith('- ') || l.slice(li) === '-') return this.seq(li);
    return this.map(li);
  }
  // Read a scalar that starts on the current line (text = remainder), consuming continuation lines deeper than ind.
  scalarFrom(text, ind) {
    const t = text.trim();
    if (t[0] === '{' || t[0] === '[') {
      // flow collections can span lines too
      let buf = t, depth = this.depth(buf);
      while (depth > 0 && this.i < this.L.length) { buf += ' ' + this.L[this.i++].trim(); depth = this.depth(buf); }
      return parseFlow(buf);
    }
    if (t[0] === "'" || t[0] === '"') {
      const q = t[0];
      const parts = [t.slice(1)];
      const closed = (s) => {
        // closing quote at end of string, not escaped
        if (q === "'") { const m = s.match(/'+$/); return m && m[0].length % 2 === 1; }
        let k = s.length - 1; if (s[k] !== '"') return false; let bs = 0; k--; while (k >= 0 && s[k] === '\\') { bs++; k--; } return bs % 2 === 0;
      };
      if (!(parts[0].length > 0 && closed(parts[0]))) {
        while (this.i < this.L.length) {
          const raw = this.L[this.i++];
          const s = raw.trim();
          parts.push(s);
          if (s.length > 0 && closed(s)) break;
        }
      }
      let last = parts[parts.length - 1]; parts[parts.length - 1] = last.slice(0, -1);
      if (q === "'") return fold(parts).replace(/''/g, "'");
      // double quoted: a trailing backslash joins lines without a space
      let joined = '';
      for (let k = 0; k < parts.length; k++) {
        let p = k === 0 ? parts[k] : parts[k];
        if (k > 0) {
          if (p === '') { joined += '\n'; continue; }
          if (joined.endsWith('\\')) { joined = joined.slice(0, -1); }
          else if (!joined.endsWith('\n')) joined += ' ';
        }
        joined += p;
      }
      return decodeDouble(joined);
    }
    // plain scalar with possible continuation lines
    const parts = [t];
    while (this.i < this.L.length) {
      const l = this.L[this.i];
      if (l.trim() === '') { // blank line inside a plain scalar only if followed by deeper text
        let j = this.i; while (j < this.L.length && this.L[j].trim() === '') j++;
        if (j < this.L.length && indentOf(this.L[j]) > ind) { for (; this.i < j; this.i++) parts.push(''); continue; }
        break;
      }
      if (indentOf(l) <= ind) break;
      parts.push(l.trim()); this.i++;
    }
    return fold(parts);
  }
  depth(s) { let d = 0, q = null; for (const c of s) { if (q) { if (c === q) q = null; continue; } if (c === "'" || c === '"') q = c; else if (c === '{' || c === '[') d++; else if (c === '}' || c === ']') d--; } return d; }
  map(ind, firstLine) {
    const o = {};
    let first = firstLine;
    for (;;) {
      let line;
      if (first !== undefined) { line = first; first = undefined; }
      else {
        const l = this.peek();
        if (l === null) break;
        const li = indentOf(l);
        if (li !== ind || l.slice(li).startsWith('- ') || l.slice(li) === '-') break;
        line = l.slice(li); this.i++;
      }
      const c = line.indexOf(': ');
      let key, rest;
      if (c >= 0) { key = line.slice(0, c); rest = line.slice(c + 2); }
      else if (line.endsWith(':')) { key = line.slice(0, -1); rest = ''; }
      else { key = line; rest = ''; }
      if (rest.trim() !== '') { o[key] = this.scalarFrom(rest, ind); continue; }
      const n = this.peek();
      if (n === null) { o[key] = ''; continue; }
      const ni = indentOf(n);
      const isSeq = n.slice(ni).startsWith('- ') || n.slice(ni) === '-';
      if (ni > ind) o[key] = this.block(ni);
      else if (ni === ind && isSeq) o[key] = this.seq(ind);
      else o[key] = '';
    }
    return o;
  }
  seq(ind, firstLine) {
    const a = [];
    let first = firstLine;
    for (;;) {
      let body;
      if (first !== undefined) { body = first; first = undefined; }
      else {
        const l = this.peek();
        if (l === null) break;
        const li = indentOf(l);
        body = l.slice(li);
        if (li !== ind || !(body.startsWith('- ') || body === '-')) break;
        this.i++;
      }
      const content = body === '-' ? '' : body.slice(2);
      const ct = content.trimStart();
      const extra = content.length - ct.length;
      if (ct.startsWith('- ') || ct === '-') { a.push(this.seq(ind + 2 + extra, ct)); continue; } // nested list on the same line: "- - item"
      if (ct === '') { const n = this.peek(); a.push(n !== null && indentOf(n) > ind ? this.block(indentOf(n)) : ''); continue; }
      const isMapItem = !/^[{\['"]/.test(ct) && (/^[^:]+: /.test(ct) || /^[^:\s][^:]*:$/.test(ct));
      if (isMapItem) a.push(this.map(ind + 2 + extra, ct));
      else a.push(this.scalarFrom(ct, ind));
    }
    return a;
  }
}

// Split a Unity YAML file into documents: [{classID, fileID, stripped, type, body}]
function parseUnityYaml(text) {
  const lines = text.split(/\r?\n/);
  const docs = [];
  let cur = null, buf = [];
  const flush = () => {
    if (!cur) return;
    const p = new Parser(buf);
    const root = p.map(0);
    const type = Object.keys(root)[0];
    cur.type = type; cur.body = root[type] || {};
    docs.push(cur);
  };
  for (const l of lines) {
    if (l.startsWith('--- !u!')) {
      flush();
      const m = l.match(/^--- !u!(\d+) &(-?\d+)( stripped)?/);
      cur = { classID: +m[1], fileID: m[2], stripped: !!m[3] }; buf = [];
    } else if (l.startsWith('%') || l.startsWith('---')) {
      if (l.startsWith('---')) { flush(); cur = { classID: 0, fileID: '0' }; buf = []; }
    } else if (cur) buf.push(l);
  }
  flush();
  return docs;
}

// Parse a whole plain YAML file (e.g. .meta) into an object.
function parsePlainYaml(text) { return new Parser(text.split(/\r?\n/).filter(l => !l.startsWith('%') && !l.startsWith('---'))).map(0); }

module.exports = { parseUnityYaml, parsePlainYaml, parseFlow };
