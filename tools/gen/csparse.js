// Declaration-level C# parser for ILSpy-decompiled sources: types, fields, methods, properties, enums.
// Statement bodies are kept as source ranges (not parsed).
'use strict';

const KEYWORDS_MOD = new Set(['public', 'private', 'protected', 'internal', 'static', 'readonly', 'const', 'abstract', 'virtual', 'override', 'sealed', 'new', 'extern', 'unsafe', 'volatile', 'partial', 'async']);

function tokenize(src) {
  const toks = []; let i = 0; const n = src.length;
  while (i < n) {
    const c = src[i];
    if (c === ' ' || c === '\t' || c === '\r' || c === '\n' || c === '﻿') { i++; continue; }
    if (c === '/' && src[i + 1] === '/') { while (i < n && src[i] !== '\n') i++; continue; }
    if (c === '/' && src[i + 1] === '*') { i += 2; while (i < n && !(src[i] === '*' && src[i + 1] === '/')) i++; i += 2; continue; }
    if (c === '#' ) { while (i < n && src[i] !== '\n') i++; continue; }
    const st = i;
    if (c === '@' && src[i + 1] === '"') { i += 2; while (i < n) { if (src[i] === '"' && src[i + 1] === '"') { i += 2; continue; } if (src[i] === '"') { i++; break; } i++; } toks.push({ t: 'str', v: src.slice(st, i), s: st, e: i }); continue; }
    if (c === '$' && src[i + 1] === '"') { i += 2; while (i < n && src[i] !== '"') { if (src[i] === '\\') i++; i++; } i++; toks.push({ t: 'str', v: src.slice(st, i), s: st, e: i }); continue; }
    if (c === '"') { i++; while (i < n && src[i] !== '"') { if (src[i] === '\\') i++; i++; } i++; toks.push({ t: 'str', v: src.slice(st, i), s: st, e: i }); continue; }
    if (c === "'") { i++; while (i < n && src[i] !== "'") { if (src[i] === '\\') i++; i++; } i++; toks.push({ t: 'chr', v: src.slice(st, i), s: st, e: i }); continue; }
    if (/[A-Za-z_@]/.test(c)) { i++; while (i < n && /[A-Za-z0-9_]/.test(src[i])) i++; toks.push({ t: 'id', v: src.slice(st, i).replace(/^@/, ''), s: st, e: i }); continue; }
    if (/[0-9]/.test(c) || (c === '.' && /[0-9]/.test(src[i + 1]))) {
      if (c === '0' && (src[i + 1] === 'x' || src[i + 1] === 'X')) { i += 2; while (i < n && /[0-9a-fA-F]/.test(src[i])) i++; }
      else { while (i < n && /[0-9.]/.test(src[i])) i++; if (src[i] === 'e' || src[i] === 'E') { i++; if (src[i] === '+' || src[i] === '-') i++; while (i < n && /[0-9]/.test(src[i])) i++; } }
      while (i < n && /[fFdDmMuUlL]/.test(src[i])) i++;
      toks.push({ t: 'num', v: src.slice(st, i), s: st, e: i }); continue;
    }
    const three = src.substr(i, 3), two = src.substr(i, 2);
    if (['<<=', '>>=', '??='].includes(three)) { i += 3; toks.push({ t: 'op', v: three, s: st, e: i }); continue; }
    if (['==', '!=', '<=', '>=', '&&', '||', '++', '--', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '=>', '??', '::', '->', '<<'].includes(two)) { i += 2; toks.push({ t: 'op', v: two, s: st, e: i }); continue; }
    i++; toks.push({ t: 'op', v: c, s: st, e: i });
  }
  return toks;
}

class Parser {
  constructor(src, file) { this.src = src; this.file = file; this.t = tokenize(src); this.i = 0; }
  peek(k = 0) { return this.t[this.i + k] || { t: 'eof', v: '' }; }
  next() { return this.t[this.i++] || { t: 'eof', v: '' }; }
  is(v, k = 0) { return this.peek(k).v === v; }
  expect(v) { const x = this.next(); if (x.v !== v) throw new Error(`${this.file}: expected '${v}' got '${x.v}' near ${this.src.slice(x.s - 40, x.s + 40)}`); return x; }
  skipBalanced(open, close) { let d = 0; for (;;) { const x = this.next(); if (x.t === 'eof') throw new Error(this.file + ': unbalanced ' + open); if (x.v === open) d++; else if (x.v === close) { d--; if (d === 0) return x; } } }
  attributes() {
    const out = [];
    while (this.is('[')) {
      const st = this.i; this.skipBalanced('[', ']');
      for (let k = st + 1; k < this.i - 1; k++) { const x = this.t[k]; if (x.t === 'id' && (this.t[k - 1].v === '[' || this.t[k - 1].v === ',')) out.push(x.v.replace(/Attribute$/, '')); }
    }
    return out;
  }
  modifiers() { const m = []; while (this.peek().t === 'id' && KEYWORDS_MOD.has(this.peek().v) && !(this.peek().v === 'new' && this.is('(', 1))) m.push(this.next().v); return m; }
  // Type: Name(.Name)*(<args>)?([])*(?)?
  type() {
    let name = this.next().v;
    if (name === 'global' && this.is('::')) { this.next(); name = this.next().v; }
    let args = [];
    for (;;) {
      if (this.is('<')) { this.next(); args = []; for (;;) { args.push(this.type()); if (this.is(',')) { this.next(); continue; } this.expect('>'); break; } }
      if (this.is('.') && this.peek(1).t === 'id') { this.next(); name += '.' + this.next().v; continue; }
      break;
    }
    let rank = 0, nullable = false;
    for (;;) {
      if (this.is('[') && (this.is(']', 1) || this.is(',', 1))) { this.next(); while (this.is(',')) this.next(); this.expect(']'); rank++; continue; }
      if (this.is('?')) { this.next(); nullable = true; continue; }
      break;
    }
    return { name, args, rank, nullable };
  }
  // initializer/default expression: tokens until , ; ) at depth 0
  exprUntil(stops) {
    const st = this.i; let d = 0;
    for (;;) {
      const x = this.peek(); if (x.t === 'eof') break;
      if (d === 0 && stops.includes(x.v)) break;
      if (x.v === '(' || x.v === '[' || x.v === '{') d++;
      else if (x.v === ')' || x.v === ']' || x.v === '}') { if (d === 0) break; d--; }
      this.next();
    }
    const toks = this.t.slice(st, this.i);
    return { toks, text: toks.length ? this.src.slice(toks[0].s, toks[toks.length - 1].e) : '' };
  }
  params(close = ')') {
    const ps = [];
    if (this.is(close)) { this.next(); return ps; }
    for (;;) {
      const attrs = this.attributes();
      let mod = null; if (['ref', 'out', 'params', 'in', 'this'].includes(this.peek().v)) mod = this.next().v;
      const ty = this.type(); const name = this.next().v; let def = null;
      if (this.is('=')) { this.next(); def = this.exprUntil([',', close]); }
      ps.push({ type: ty, name, def, mod, attrs });
      if (this.is(',')) { this.next(); continue; }
      this.expect(close); break;
    }
    return ps;
  }
  body() {
    // method body: { ... } | ; | => expr ;
    if (this.is(';')) { this.next(); return null; }
    if (this.is('=>')) { this.next(); const st = this.peek().s; const e = this.exprUntil([';']); this.expect(';'); return { s: st, e: e.toks.length ? e.toks[e.toks.length - 1].e : st, expr: true }; }
    const open = this.peek(); const close = this.skipBalanced('{', '}');
    return { s: open.s, e: close.e };
  }
  typeDecl(attrs, mods, outer) {
    const kind = this.next().v; // class struct enum interface delegate
    if (kind === 'delegate') {
      const ret = this.type(); const name = this.next().v; this.expect('('); const ps = this.params(); this.expect(';');
      return { kind, name, ret, params: ps, attrs, mods, outer };
    }
    const name = this.next().v;
    let generic = null; if (this.is('<')) { const st = this.i; this.skipBalanced('<', '>'); generic = this.t.slice(st, this.i).map(x => x.v).join(''); }
    const bases = [];
    if (this.is(':')) { this.next(); for (;;) { bases.push(this.type()); if (this.is(',')) { this.next(); continue; } break; } }
    while (this.is('where')) { while (!this.is('{')) this.next(); }
    const decl = { kind, name, generic, bases, attrs, mods, outer, fields: [], methods: [], props: [], nested: [], enumValues: [], events: [], ctors: [] };
    this.expect('{');
    if (kind === 'enum') {
      let next = 0;
      while (!this.is('}')) {
        this.attributes();
        const n = this.next().v; let val = null;
        if (this.is('=')) { this.next(); val = this.exprUntil([',', '}']).text; }
        decl.enumValues.push({ name: n, value: val });
        if (this.is(',')) this.next();
      }
      this.expect('}'); if (this.is(';')) this.next();
      return decl;
    }
    while (!this.is('}')) this.member(decl);
    this.expect('}'); if (this.is(';')) this.next();
    return decl;
  }
  member(decl) {
    const attrs = this.attributes();
    const mods = this.modifiers();
    const p = this.peek();
    if (['class', 'struct', 'enum', 'interface', 'delegate'].includes(p.v)) { decl.nested.push(this.typeDecl(attrs, mods, decl)); return; }
    if (p.v === 'event') { this.next(); const ty = this.type(); const name = this.next().v; if (this.is('{')) this.skipBalanced('{', '}'); else { while (!this.is(';')) this.next(); this.next(); } decl.events.push({ type: ty, name, mods }); return; }
    if (p.v === '~') { this.next(); this.next(); this.expect('('); this.params(); this.body(); return; }
    if (p.t === 'id' && p.v === decl.name && this.is('(', 1)) {
      this.next(); this.expect('('); const ps = this.params();
      let init = null; if (this.is(':')) { this.next(); const k = this.next().v; this.expect('('); const st = this.i; this.i--; this.skipBalanced('(', ')'); init = { kind: k, text: this.src.slice(this.t[st].s, this.t[this.i - 1].s) }; }
      const b = this.body(); decl.ctors.push({ params: ps, mods, attrs, body: b, init, static: mods.includes('static') }); return;
    }
    if (p.v === 'implicit' || p.v === 'explicit') { this.next(); this.next(); this.type(); this.expect('('); this.params(); this.body(); return; }
    const ty = this.type();
    if (this.is('operator')) { this.next(); this.next(); if (this.peek().v !== '(') this.next(); this.expect('('); this.params(); this.body(); return; }
    if (this.is('this') && this.is('[', 1)) { this.next(); this.next(); this.params(']'); this.skipBalanced('{', '}'); return; }
    const nameTok = this.next(); let name = nameTok.v;
    // explicit interface implementation: IFoo.Bar
    while (this.is('.')) { this.next(); name = this.next().v; }
    if (this.is('<')) this.skipBalanced('<', '>');
    if (this.is('(')) {
      this.next(); const ps = this.params();
      while (this.is('where')) { while (!this.is('{') && !this.is(';')) this.next(); }
      const b = this.body();
      decl.methods.push({ name, ret: ty, params: ps, mods, attrs, body: b }); return;
    }
    if (this.is('{') || this.is('=>')) {
      // property
      const prop = { name, type: ty, mods, attrs, get: null, set: null, auto: false };
      if (this.is('=>')) { this.next(); const st = this.peek().s; const e = this.exprUntil([';']); this.expect(';'); prop.get = { s: st, e: e.toks[e.toks.length - 1].e, expr: true }; }
      else {
        this.expect('{');
        while (!this.is('}')) {
          this.attributes(); this.modifiers();
          const acc = this.next().v; const b = this.body();
          if (acc === 'get') prop.get = b || { auto: true }; else if (acc === 'set') prop.set = b || { auto: true };
          if (!b) prop.auto = true;
        }
        this.expect('}');
        if (this.is('=')) { this.next(); prop.init = this.exprUntil([';']); this.expect(';'); }
      }
      decl.props.push(prop); return;
    }
    // field(s)
    for (;;) {
      let init = null;
      if (this.is('=')) { this.next(); init = this.exprUntil([',', ';']); }
      decl.fields.push({ name, type: ty, mods, attrs, init });
      if (this.is(',')) { this.next(); name = this.next().v; continue; }
      this.expect(';'); break;
    }
  }
  unit() {
    const types = [];
    while (this.peek().t !== 'eof') {
      if (this.is('using')) { while (!this.is(';')) this.next(); this.next(); continue; }
      if (this.is('namespace')) { this.next(); this.type(); this.expect('{'); continue; }
      if (this.is('}')) { this.next(); continue; }
      const attrs = this.attributes(); const mods = this.modifiers();
      if (['class', 'struct', 'enum', 'interface', 'delegate'].includes(this.peek().v)) types.push(this.typeDecl(attrs, mods, null));
      else throw new Error(this.file + ': unexpected ' + this.peek().v);
    }
    return types;
  }
}

function parseFile(src, file) { return new Parser(src, file).unit(); }
module.exports = { parseFile, tokenize };
