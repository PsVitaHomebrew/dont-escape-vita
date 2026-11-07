// Generates C++ declarations, registry and stub bodies for the game's C# scripts.
// Usage: node gen.js <Assembly-CSharp folder> <engine/src/game folder> [--chunks-only]
//  - game_types.h          forward declarations, enums, delegates, the struct
//  - h/<Class>.h           class declarations (fields, methods)
//  - registry.gen.cpp      ClassInfo (messages, Invoke dispatch), _load, _clearRefs, statics
//  - stubs/<Class>.cpp     default method bodies (used until cpp/<Class>.cpp exists)
//  - game_N.cpp            build chunks that include cpp/ or stubs/ files
//  - manifest.json         per class: file, base, methods, which messages, line counts (for translators)
'use strict';
const fs = require('fs'), path = require('path');
const { parseFile } = require('./csparse');

const SRC = path.resolve(process.argv[2]);
const OUT = path.resolve(process.argv[3]);
const CHUNKS_ONLY = process.argv.includes('--chunks-only');
const NCHUNK = 12;

const files = fs.readdirSync(SRC).filter(f => f.endsWith('.cs')).sort();
const types = [];
for (const f of files) {
  const src = fs.readFileSync(path.join(SRC, f), 'utf8');
  for (const t of parseFile(src, f)) { t.file = f; t.src = src; types.push(t); }
}
const execOrder = {};
for (const f of files) {
  const m = fs.existsSync(path.join(SRC, f + '.meta')) ? fs.readFileSync(path.join(SRC, f + '.meta'), 'utf8').match(/executionOrder: (-?\d+)/) : null;
  execOrder[f.replace(/\.cs$/, '')] = m ? +m[1] : 0;
}

// ------------------------------------------------------------------ symbol tables
const classes = new Map();   // name -> decl (class/struct)
const enums = new Map();     // C# name ("Outer.Inner" or "Name") -> cpp name
const delegates = new Map(); // C# name -> { cpp, decl }
for (const t of types) {
  if (t.kind === 'class' || t.kind === 'struct') classes.set(t.name, t);
  if (t.kind === 'enum') enums.set(t.name, t.name);
  if (t.kind === 'delegate') delegates.set(t.name, { cpp: t.name, decl: t });
  for (const n of t.nested || []) {
    const cpp = t.name + '_' + n.name;
    if (n.kind === 'enum') enums.set(t.name + '.' + n.name, cpp);
    else if (n.kind === 'delegate') delegates.set(t.name + '.' + n.name, { cpp, decl: n });
    else throw new Error('nested ' + n.kind + ' not supported: ' + cpp);
  }
}
const UNITY_CLASSES = new Set(['Object', 'GameObject', 'Component', 'Transform', 'Behaviour', 'MonoBehaviour', 'Renderer', 'SpriteRenderer', 'Sprite', 'Texture', 'Texture2D', 'RenderTexture', 'AudioClip', 'AudioSource', 'AudioListener', 'AudioReverbFilter', 'Animator', 'AnimationClip', 'RuntimeAnimatorController', 'Camera', 'Collider2D', 'BoxCollider2D', 'CircleCollider2D', 'PolygonCollider2D', 'TextAsset', 'Material', 'Shader', 'SpriteMask', 'GUILayer', 'FlareLayer', 'Rigidbody2D', 'FileStream']);
const UNITY_VALUES = new Set(['Vector2', 'Vector3', 'Vector4', 'Color', 'Rect', 'Bounds', 'Quaternion', 'Matrix4x4', 'Resolution', 'RaycastHit2D', 'LayerMask', 'AnimatorStateInfo', 'AnimatorClipInfo', 'Scene', 'DateTime', 'KeyCode', 'FilterMode', 'CameraClearFlags', 'SpriteMaskInteraction', 'AudioReverbPreset', 'StringBuilder', 'SteamAPIWarningMessageHook_t', 'BinaryFormatter', 'FileMode']);
const PRIM = { bool: 'bool', int: 'int', float: 'float', double: 'double', long: 'long long', byte: 'uint8_t', sbyte: 'int8_t', short: 'short', ushort: 'uint16_t', uint: 'unsigned', ulong: 'unsigned long long', char: 'char16_t', void: 'void', string: 'String', String: 'String', object: 'P<Obj>', Object: 'P<Object>', Single: 'float', Int32: 'int', Boolean: 'bool' };
const RENAME = { S: 'S_', alive: 'alive_', P: 'P_', str: 'str_', New: 'New_', log: 'log_', NULL: 'NULL_', EOF: 'EOF_', TRUE: 'TRUE_', FALSE: 'FALSE_', ERROR: 'ERROR_', DOMAIN: 'DOMAIN_', OVERFLOW: 'OVERFLOW_', min: 'min_', max: 'max_' };
const cppName = n => RENAME[n] || n;
const unknownTypes = new Map();

function baseChain(name) { const out = []; let c = classes.get(name); while (c) { out.push(c); const b = c.bases[0] && c.bases[0].name; c = b && classes.get(b); } return out; }
function isMB(name) { let c = classes.get(name); while (c) { const b = c.bases[0] && c.bases[0].name.replace(/^UnityEngine\./, ''); if (!b) return false; if (b === 'MonoBehaviour') return true; c = classes.get(b); } return false; }

function stripNs(n) { return n.replace(/^(UnityEngine|System\.Collections\.Generic|System\.Collections|System|UnityEngine\.SceneManagement)\./, ''); }
function resolveNested(name, ctx, map) {
  // Look for Name in ctx class chain, then globally
  if (map.has(name)) return map.get(name);
  if (ctx) for (const c of baseChain(ctx)) if (map.has(c.name + '.' + name)) return map.get(c.name + '.' + name);
  return null;
}
function cppType(ty, ctx, where) {
  let inner;
  const n = stripNs(ty.name);
  if (PRIM[n]) inner = PRIM[n];
  else if (n === 'List' && ty.args.length === 1) inner = 'List<' + cppType(ty.args[0], ctx, where) + '>';
  else if (n === 'Action') inner = 'std::function<void(' + ty.args.map(a => cppType(a, ctx, where)).join(', ') + ')>';
  else if (n === 'Func') { const a = ty.args.map(x => cppType(x, ctx, where)); inner = 'std::function<' + a[a.length - 1] + '(' + a.slice(0, -1).join(', ') + ')>'; }
  else if (UNITY_CLASSES.has(n)) inner = 'P<' + n + '>';
  else if (UNITY_VALUES.has(n)) inner = n;
  else if (resolveNested(n, ctx, enums)) inner = resolveNested(n, ctx, enums);
  else if (resolveNested(n, ctx, delegates)) inner = resolveNested(n, ctx, delegates).cpp;
  else if (classes.has(n)) inner = classes.get(n).kind === 'struct' ? n : 'P<' + n + '>';
  else if (n === 'IEnumerator') inner = 'P<Obj>';
  else { unknownTypes.set(ty.name, (unknownTypes.get(ty.name) || []).concat(where)); inner = 'P<Obj> /*' + ty.name + '*/'; }
  for (let r = 0; r < ty.rank; r++) inner = 'Array<' + inner + '>';
  return inner;
}
const isRefLike = cpp => /^(P<|List<|Array<|std::function)/.test(cpp) || [...delegates.values()].some(d => d.cpp === cpp);

// ------------------------------------------------------------------ simple initializer translation
function cppNum(v) {
  let s = v; let suffix = '';
  const m = s.match(/[fFdDmMuUlL]+$/); if (m) { suffix = m[0].toLowerCase(); s = s.slice(0, -m[0].length); }
  if (/^0x/i.test(s)) return s + (suffix.includes('u') ? 'u' : '');
  const isFloat = suffix.includes('f');
  const isDouble = suffix.includes('d') || suffix.includes('m') || (!isFloat && /[.eE]/.test(s));
  if (isFloat || isDouble) { if (!/[.eE]/.test(s)) s += '.0'; if (s.startsWith('.')) s = '0' + s; if (/\.$/.test(s)) s += '0'; return s + (isFloat ? 'f' : ''); }
  if (suffix.includes('l')) return s + 'LL';
  if (suffix.includes('u')) return s + 'u';
  return s;
}
function cppStringLiteral(tok) {
  let body;
  if (tok.startsWith('@"')) body = tok.slice(2, -1).replace(/""/g, '"').replace(/\\/g, '\\\\').replace(/"/g, '\\"').replace(/\r?\n/g, '\\n');
  else body = tok.slice(1, -1);
  return 'S("' + body + '")';
}
function cppChar(tok) { return 'u' + tok; }
function simpleExpr(toks, ctx, fieldType) {
  if (!toks || !toks.length) return null;
  const v = toks.map(t => t.v);
  if (toks.length === 1) {
    const t = toks[0];
    if (t.t === 'num') return cppNum(t.v);
    if (t.t === 'str') return cppStringLiteral(t.v);
    if (t.t === 'chr') return cppChar(t.v);
    if (t.v === 'true' || t.v === 'false') return t.v;
    if (t.v === 'null') return 'nullptr';
  }
  if (toks.length === 2 && v[0] === '-' && toks[1].t === 'num') return '-' + cppNum(toks[1].v);
  if (v.join('') === 'string.Empty' || v.join('') === 'String.Empty') return 'String(u"")';
  // Enum.Member / Outer.Enum.Member / Unity statics
  const joined = v.join('');
  if (/^[A-Za-z_][\w.]*$/.test(joined)) {
    const parts = joined.split('.');
    if (parts.length >= 2) {
      const en = parts.slice(0, -1).join('.'); const mem = parts[parts.length - 1];
      const r = resolveNested(stripNs(en), ctx, enums);
      if (r) return r + '::' + cppName(mem);
      if (stripNs(en) === 'KeyCode') return 'KeyCode::' + ({ P: 'Pp', S: 'S_' }[mem] || mem);
      if (['Color', 'Vector2', 'Vector3'].includes(stripNs(en)) && /^[a-z]/.test(mem)) return stripNs(en) + '::get_' + mem + '()';
    }
  }
  // new List<T>()
  if (v[0] === 'new') {
    let i = 1; const nameToks = [];
    // collect type tokens up to '(' or '['
    while (i < v.length && v[i] !== '(' && v[i] !== '[' && v[i] !== '{') { nameToks.push(v[i]); i++; }
    const tn = nameToks.join('');
    if (/^(System\.Collections\.Generic\.)?List<.+>$/.test(tn) && v.slice(i).join('') === '()') return fieldType + '::New()';
    if (v[i] === '[' && /^\[\d+\]$/.test(v.slice(i).join('')) && fieldType.startsWith('Array<')) return fieldType + '::New(' + v[i + 1] + ')';
    if (['Vector2', 'Vector3', 'Vector4', 'Color', 'Rect'].includes(stripNs(tn)) && v[i] === '(' && v[v.length - 1] === ')') {
      const args = []; let cur = [];
      for (const t of toks.slice(i + 1, -1)) { if (t.v === ',') { args.push(cur); cur = []; } else cur.push(t); }
      if (cur.length) args.push(cur);
      const conv = args.map(a => simpleExpr(a, ctx, 'float'));
      if (conv.every(x => x !== null && /^-?[\d.]+f?$/.test(x))) return stripNs(tn) + '(' + conv.join(', ') + ')';
    }
  }
  return null;
}

// ------------------------------------------------------------------ per-class model
const MSG = ['Awake', 'Start', 'Update', 'LateUpdate', 'OnEnable', 'OnDisable', 'OnDestroy', 'OnMouseDown', 'OnMouseUp', 'OnMouseEnter', 'OnMouseExit', 'OnMouseOver'];
const model = [];
for (const c of types) {
  if (c.kind !== 'class' && c.kind !== 'struct') continue;
  const baseName = c.bases[0] ? stripNs(c.bases[0].name) : null;
  const gameBase = baseName && classes.has(baseName) ? baseName : null;
  const mb = isMB(c.name);
  const cppBase = c.kind === 'struct' ? null : gameBase ? gameBase : baseName === 'MonoBehaviour' ? 'MonoBehaviour' : (baseName && UNITY_CLASSES.has(baseName)) ? baseName : 'Obj';
  const abstract = c.mods.includes('abstract');
  const fields = c.fields.map(f => {
    const isConst = f.mods.includes('const'), isStatic = f.mods.includes('static') || isConst;
    const ty = cppType(f.type, c.name, c.name + '.' + f.name);
    const init = f.init ? simpleExpr(f.init.toks, c.name, ty) : null;
    return { cs: f, name: cppName(f.name), type: ty, isStatic, isConst, init, complex: f.init && init === null ? f.init.text : null };
  });
  const methods = c.methods.map(m => {
    const ret = cppType(m.ret, c.name, c.name + '.' + m.name + '()');
    const params = m.params.map(p => {
      let ty = cppType(p.type, c.name, c.name + '.' + m.name + '(' + p.name + ')');
      if (p.mod === 'ref' || p.mod === 'out') ty += '&';
      let def = p.def ? simpleExpr(p.def.toks, c.name, ty) : null;
      if (p.def && def === null) def = '/*default: ' + p.def.text + '*/{}';
      return { name: cppName(p.name), type: ty, def, csType: stripNs(p.type.name) + (p.type.rank ? '[]' : '') };
    });
    return { cs: m, name: cppName(m.name), ret, params, isStatic: m.mods.includes('static'), isAbstract: m.mods.includes('abstract'), isVirtual: m.mods.includes('virtual'), isOverride: m.mods.includes('override'), lines: m.body ? c.src.slice(m.body.s, m.body.e).split('\n').length : 0 };
  });
  // C# prefers an overload without optional arguments; drop defaults that would make C++ calls ambiguous
  for (const f of methods) for (const g of methods) {
    if (f === g || f.name !== g.name || g.params.length >= f.params.length) continue;
    const required = f.params.findIndex(p => p.def); if (required < 0 || g.params.length < required) continue;
    for (let k = g.params.length; k < f.params.length; k++) f.params[k].def = null;
    for (let k = f.params.length - 1; k >= 0 && !f.params[k].def; k--) {} 
  }
  // C++ needs every parameter after a defaulted one to have a default too
  for (const f of methods) { let seenNonDef = false; for (let k = f.params.length - 1; k >= 0; k--) { if (!f.params[k].def) seenNonDef = true; else if (seenNonDef) f.params[k].def = null; } }
  const props = c.props.map(p => ({ cs: p, name: cppName(p.name), type: cppType(p.type, c.name, c.name + '.' + p.name), isStatic: p.mods.includes('static'), auto: p.auto, hasGet: !!p.get, hasSet: !!p.set, isOverride: p.mods.includes('override'), isVirtual: p.mods.includes('virtual') || p.mods.includes('abstract') }));
  const ctors = c.ctors.filter(k => !k.static).map(k => ({ cs: k, params: k.params.map(p => ({ name: cppName(p.name), type: cppType(p.type, c.name, c.name + '.ctor'), def: p.def ? simpleExpr(p.def.toks, c.name, '') : null })) }));
  const needsCtor = ctors.length > 0 || fields.some(f => !f.isStatic && f.complex);
  const needsCctor = fields.some(f => f.isStatic && !f.isConst && f.complex) || fields.some(f => f.isConst && f.complex);
  model.push({ c, name: c.name, file: c.file, kind: c.kind, baseName, gameBase, cppBase, mb, abstract, fields, methods, props, ctors, needsCtor, needsCctor, serializable: c.attrs.includes('Serializable') });
}
const byName = new Map(model.map(m => [m.name, m]));

// ------------------------------------------------------------------ writers
function hdrFor(m) {
  const L = [];
  L.push(`// Generated from ${m.file} by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/${m.name}.cpp`);
  L.push('#pragma once');
  L.push('#include "../game_types.h"');
  if (m.gameBase) L.push(`#include "${m.gameBase}.h"`);
  L.push('');
  const kw = m.kind === 'struct' ? 'struct' : 'class';
  L.push(`${kw} ${m.name}${m.cppBase ? ' : public ' + m.cppBase : ''} {`);
  L.push('public:');
  for (const n of (m.c.nested || [])) L.push(`  using ${n.name} = ${m.name}_${n.name};`);
  if (m.fields.length) L.push('  // ---- fields');
  for (const f of m.fields) {
    if (f.isConst) {
      const constexprOk = f.init !== null && /^(int|float|double|bool|long long|unsigned|char16_t|uint8_t)$/.test(f.type);
      if (constexprOk) L.push(`  static constexpr ${f.type} ${f.name} = ${f.init};`);
      else L.push(`  static ${f.type} ${f.name}; // const${f.complex ? ' = ' + f.complex.replace(/\s+/g, ' ') + ' (set in _cctor)' : ''}`);
    } else if (f.isStatic) L.push(`  static ${f.type} ${f.name};${f.complex ? ' // = ' + f.complex.replace(/\s+/g, ' ') + '  (set in _cctor)' : ''}`);
    else L.push(`  ${f.type} ${f.name}${f.init !== null ? ' = ' + f.init : '{}'};${f.complex ? ' // C# init: ' + f.complex.replace(/\s+/g, ' ') + '  (do it in the constructor)' : ''}`);
  }
  for (const p of m.props) if (p.auto) L.push(`  ${p.isStatic ? 'static ' : ''}${p.type} _${p.name}_k${p.isStatic ? '' : '{}'}; // auto-property backing`);
  L.push('  // ---- constructors');
  if (!m.needsCtor) L.push(`  ${m.name}() {}`);
  else { if (!m.ctors.some(k => k.params.length && k.params.every(p => p.def))) L.push(`  ${m.name}();`); for (const k of m.ctors) if (k.params.length) L.push(`  ${m.name}(${k.params.map(p => p.type + ' ' + p.name + (p.def ? ' = ' + p.def : '')).join(', ')});`); }
  if (m.props.length) L.push('  // ---- properties');
  for (const p of m.props) {
    const st = p.isStatic ? 'static ' : (p.isVirtual ? 'virtual ' : '');
    if (p.hasGet) L.push(`  ${st}${p.type} get_${p.name}()${p.isOverride ? ' override' : ''};`);
    if (p.hasSet) L.push(`  ${st}void set_${p.name}(${p.type} value)${p.isOverride ? ' override' : ''};`);
  }
  if (m.methods.length) L.push('  // ---- methods');
  for (const f of m.methods) {
    const gameVirtualBase = f.isOverride && m.gameBase && baseChain(m.gameBase).some(b => b.methods.some(x => x.name === f.cs.name && (x.mods.includes('virtual') || x.mods.includes('abstract') || x.mods.includes('override'))));
    const pre = f.isStatic ? 'static ' : (f.isVirtual || f.isAbstract || (f.isOverride && !gameVirtualBase)) ? 'virtual ' : '';
    const post = f.isAbstract ? ' = 0' : gameVirtualBase ? ' override' : '';
    L.push(`  ${pre}${f.ret} ${f.name}(${f.params.map(p => p.type + ' ' + p.name + (p.def ? ' = ' + p.def : '')).join(', ')})${post};`);
  }
  L.push('  // ---- generated');
  if (m.needsCctor) L.push('  static void _cctor(); // translator: set the static fields marked (set in _cctor)');
  if (m.kind === 'struct') { L.push('  void _load(FieldReader& r);'); L.push('  void _save(JsonWriter& w);'); }
  else { L.push(`  void _load(FieldReader& r)${m.mb ? ' override' : ''};`); L.push(`  void _clearRefs()${m.mb ? ' override' : ''};`); if (!m.mb) L.push('  void _save(JsonWriter& w);'); }
  if (m.mb) { L.push('  const ClassInfo* _getClassInfo() const override;'); L.push('  void _saveSerialized(JsonWriter& w) override;'); }
  L.push('};');
  return L.join('\n') + '\n';
}

function defaultReturn(t) { if (t === 'void') return ''; if (t === 'bool') return ' return false;'; return ' return {};'; }
function stubFor(m) {
  const L = [`// STUB generated by tools/gen/gen.js for ${m.name} (replace by translating into src/game/cpp/${m.name}.cpp)`, '#include "../game_all.h"', ''];
  if (m.needsCtor) { if (!m.ctors.some(k => k.params.length && k.params.every(p => p.def))) L.push(`${m.name}::${m.name}() {}`); for (const k of m.ctors) if (k.params.length) L.push(`${m.name}::${m.name}(${k.params.map(p => p.type + ' ' + p.name).join(', ')}) {}`); }
  for (const p of m.props) {
    if (p.hasGet) L.push(`${p.type} ${m.name}::get_${p.name}() {${p.auto ? ' return _' + p.name + '_k;' : defaultReturn(p.type)} }`);
    if (p.hasSet) L.push(`void ${m.name}::set_${p.name}(${p.type} value) {${p.auto ? ' _' + p.name + '_k = value;' : ''} }`);
  }
  for (const f of m.methods) if (!f.isAbstract) L.push(`${f.ret} ${m.name}::${f.name}(${f.params.map(p => p.type + ' ' + p.name).join(', ')}) {${defaultReturn(f.ret)} }`);
  if (m.needsCctor) L.push(`void ${m.name}::_cctor() {}`);
  return L.join('\n') + '\n';
}

const delegateCpp = new Set([...delegates.values()].map(d => d.cpp));
function readable(t) { return !/^std::function|P<Obj>|SteamAPIWarningMessageHook_t|StringBuilder/.test(t) && !delegateCpp.has(t) && ![...delegateCpp].some(d => t.includes('<' + d + '>')); }
const NOT_SERIALIZED_VALUES = new Set(['Bounds', 'Quaternion', 'Matrix4x4', 'DateTime', 'Scene', 'StringBuilder', 'SteamAPIWarningMessageHook_t', 'BinaryFormatter', 'FileMode', 'RaycastHit2D', 'AnimatorStateInfo', 'AnimatorClipInfo', 'Resolution']);
function serializableType(ty, ctx, inList) {
  const n = stripNs(ty.name);
  if (ty.rank > 1 || (inList && ty.rank > 0)) return false;
  if (n === 'List') return ty.rank === 0 && !inList && ty.args.length === 1 && serializableType(ty.args[0], ctx, true);
  if (ty.rank === 1) return serializableType({ ...ty, rank: 0 }, ctx, true);
  if (PRIM[n]) return !['object', 'void'].includes(n);
  if (UNITY_CLASSES.has(n)) return n !== 'FileStream';
  if (UNITY_VALUES.has(n)) return !NOT_SERIALIZED_VALUES.has(n);
  if (resolveNested(n, ctx, enums)) return true;
  if (classes.has(n)) { const mm = byName.get(n); return mm.mb || mm.serializable; }
  return false;
}
function unitySerialized(f, m) {
  const mods = f.cs.mods, attrs = f.cs.attrs;
  if (f.isStatic || f.isConst || mods.includes('readonly')) return false;
  if (attrs.includes('NonSerialized')) return false;
  if (!(mods.includes('public') || attrs.includes('SerializeField'))) return false;
  return readable(f.type) && serializableType(f.cs.type, m.name, false);
}
function registryCpp() {
  const L = ['// Generated by tools/gen/gen.js - do not edit.', '#include "game_all.h"', '#include <cstring>', ''];
  // statics
  for (const m of model) for (const f of m.fields) {
    if (!f.isStatic) continue;
    if (f.isConst && f.init !== null && /^(int|float|double|bool|long long|unsigned|char16_t|uint8_t)$/.test(f.type)) continue;
    L.push(`${f.type} ${m.name}::${f.name}${f.init !== null ? ' = ' + f.init : '{}'};`);
  }
  for (const m of model) for (const p of m.props) if (p.auto && p.isStatic) L.push(`${p.type} ${m.name}::_${p.name}_k{};`);
  L.push('');
  L.push('void gameStaticInit() {');
  for (const m of model) if (m.needsCctor) L.push(`  ${m.name}::_cctor();`);
  L.push('}');
  L.push('');
  for (const m of model) {
    // _load / _clearRefs
    L.push(`void ${m.name}::_load(FieldReader& _r) {`);
    if (m.gameBase) L.push(`  ${m.gameBase}::_load(_r);`);
    for (const f of m.fields) if (!f.isStatic && readable(f.type)) L.push(`  _r.get("${f.cs.name}", ${f.name});`);
    L.push('}');
    if (m.mb) {
      // the fields Unity serializes, so Instantiate can copy a live object the way Unity does
      L.push(`void ${m.name}::_saveSerialized(JsonWriter& _w) {`);
      if (m.gameBase) L.push(`  ${m.gameBase}::_saveSerialized(_w);`);
      for (const f of m.fields) if (unitySerialized(f, m)) L.push(`  _w.put("${f.cs.name}", ${f.name});`);
      L.push('}');
    }
    if (!m.mb) {
      L.push(`void ${m.name}::_save(JsonWriter& _w) {`);
      if (m.gameBase) L.push(`  ${m.gameBase}::_save(_w);`);
      for (const f of m.fields) if (!f.isStatic && readable(f.type)) L.push(`  _w.put("${f.cs.name}", ${f.name});`);
      L.push('}');
    }
    if (m.kind !== 'struct') {
      L.push(`void ${m.name}::_clearRefs() {`);
      if (m.gameBase) L.push(`  ${m.gameBase}::_clearRefs();`);
      for (const f of m.fields) if (!f.isStatic && isRefLike(f.type)) L.push(`  ${f.name} = nullptr;`);
      L.push('}');
    }
  }
  L.push('');
  // enum names
  for (const t of types) {
    const add = (decl, cpp) => {
      L.push(`String str(${cpp} v) { switch (v) {`);
      const seen = new Set();
      for (const e of decl.enumValues) { if (seen.has(e.name)) continue; seen.add(e.name); L.push(`  case ${cpp}::${cppName(e.name)}: return S("${e.name}");`); }
      L.push('  default: return str((int)v); } }');
    };
    if (t.kind === 'enum') add(t, t.name);
    for (const n of t.nested || []) if (n.kind === 'enum') add(n, t.name + '_' + n.name);
  }
  L.push('');
  // ClassInfo for MonoBehaviours
  const mbs = model.filter(m => m.mb);
  const findOwner = (m, name, argc) => { for (const c of baseChain(m.name)) { const mm = byName.get(c.name); const f = mm.methods.find(x => x.cs.name === name && x.params.length === argc && !x.isStatic); if (f) return { owner: mm, f }; } return null; };
  for (const m of mbs) L.push(`static bool _inv_${m.name}(MonoBehaviour* mb, const char* n, const EventArg& a);`);
  for (const m of mbs) {
    L.push(`static bool _inv_${m.name}(MonoBehaviour* mb, const char* n, const EventArg& a) {`);
    L.push(`  ${m.name}* t = static_cast<${m.name}*>(mb); (void)t; (void)a;`);
    const seen = new Set();
    const one = m.methods.filter(f => !f.isStatic && !f.isAbstract && f.params.length === 1 && /^(String|float|int|bool|P<Object>)$/.test(f.params[0].type));
    const zero = m.methods.filter(f => !f.isStatic && !f.isAbstract && f.params.length === 0);
    const names = [...new Set([...one, ...zero].map(f => f.cs.name))];
    for (const nm of names) {
      const z = zero.find(f => f.cs.name === nm), o = one.find(f => f.cs.name === nm);
      const call1 = o ? (o.params[0].type === 'String' ? 't->' + o.name + '(a.s)' : o.params[0].type === 'float' ? 't->' + o.name + '(a.f)' : o.params[0].type === 'int' ? 't->' + o.name + '(a.i)' : o.params[0].type === 'bool' ? 't->' + o.name + '(a.i != 0)' : 't->' + o.name + '(a.o)') : null;
      const call0 = z ? 't->' + z.name + '()' : null;
      let body;
      if (call0 && call1) body = `if (a.has) ${call1}; else ${call0};`; else body = (call1 || call0) + ';';
      L.push(`  if (!strcmp(n, "${nm}")) { ${body} return true; }`);
      seen.add(nm);
    }
    if (m.gameBase && byName.get(m.gameBase).mb) L.push(`  return _inv_${m.gameBase}(mb, n, a);`); else L.push('  return false;');
    L.push('}');
  }
  for (const m of mbs) {
    L.push(`static const ClassInfo _ci_${m.name} = [] {`);
    L.push(`  ClassInfo c; c.name = "${m.name}"; c.base = "${m.baseName}"; c.execOrder = ${execOrder[m.name] || 0};`);
    if (!m.abstract) L.push(`  c.create = []() -> MonoBehaviour* { return new ${m.name}(); };`);
    for (const msg of MSG) { const o = findOwner(m, msg, 0); if (o) L.push(`  c.${msg} = [](MonoBehaviour* mb) { static_cast<${m.name}*>(mb)->${o.f.isVirtual || o.f.isOverride ? '' : o.owner.name + '::'}${o.f.name}(); };`); }
    const lw = findOwner(m, 'OnLevelWasLoaded', 1); if (lw) L.push(`  c.OnLevelWasLoaded = [](MonoBehaviour* mb, int lv) { static_cast<${m.name}*>(mb)->${lw.owner.name}::OnLevelWasLoaded(lv); };`);
    L.push(`  c.invoke = _inv_${m.name};`);
    L.push('  return c; }();');
    L.push(`const ClassInfo* ${m.name}::_getClassInfo() const { return &_ci_${m.name}; }`);
  }
  L.push('');
  L.push('static struct _RegisterAll { _RegisterAll() {');
  for (const m of mbs) L.push(`  registerClass(&_ci_${m.name});`);
  L.push('} } _registerAll;');
  return L.join('\n') + '\n';
}

function typesH() {
  const L = ['// Generated by tools/gen/gen.js - do not edit.', '#pragma once', '#include "../unity.h"', '#include "../registry.h"', '#include "../stores.h"', ''];
  for (const m of model) L.push(`${m.kind === 'struct' ? 'struct' : 'class'} ${m.name};`);
  L.push('');
  const enumDecl = (decl, cpp) => {
    L.push(`enum class ${cpp} : int { ${decl.enumValues.map(e => cppName(e.name) + (e.value !== null ? ' = ' + e.value.replace(/\b([A-Za-z_]\w*)\b/g, (w) => decl.enumValues.some(x => x.name === w) ? cppName(w) : w) : '')).join(', ')} };`);
    L.push(`String str(${cpp} v);`);
  };
  for (const t of types) { if (t.kind === 'enum') enumDecl(t, t.name); for (const n of t.nested || []) if (n.kind === 'enum') enumDecl(n, t.name + '_' + n.name); }
  L.push('');
  // value struct(s) are needed complete by other headers
  for (const m of model) if (m.kind === 'struct') { L.push(hdrFor(m).split('\n').filter(l => !l.startsWith('#') && !l.startsWith('//')).join('\n')); }
  for (const [csName, d] of delegates) {
    const ctx = d.decl.outer ? d.decl.outer.name : null;
    L.push(`using ${d.cpp} = std::function<${cppType(d.decl.ret, ctx, csName)}(${d.decl.params.map(p => cppType(p.type, ctx, csName)).join(', ')})>;`);
  }
  L.push('void gameStaticInit();');
  return L.join('\n') + '\n';
}

function topoOrder() {
  const done = new Set(), out = [];
  const visit = m => { if (done.has(m.name)) return; if (m.gameBase) visit(byName.get(m.gameBase)); done.add(m.name); out.push(m); };
  model.forEach(visit); return out;
}

function writeChunks() {
  const cppDir = path.join(OUT, 'cpp');
  fs.mkdirSync(cppDir, { recursive: true });
  const names = model.filter(m => m.kind !== 'struct' || m.methods.length || m.needsCtor).map(m => m.name);
  // KeyValueString methods (if any) also need a body file
  const translated = names.filter(n => fs.existsSync(path.join(cppDir, n + '.cpp')));
  const chunks = Array.from({ length: NCHUNK }, () => []);
  names.forEach((n, i) => chunks[i % NCHUNK].push(n));
  for (let k = 0; k < NCHUNK; k++) {
    const L = ['// Generated build chunk - includes translated code where present, stubs otherwise.', '#include "game_all.h"'];
    for (const n of chunks[k]) L.push(fs.existsSync(path.join(cppDir, n + '.cpp')) ? `#include "cpp/${n}.cpp"` : `#include "stubs/${n}.cpp"`);
    fs.writeFileSync(path.join(OUT, `game_${k}.cpp`), L.join('\n') + '\n');
  }
  console.log(`chunks: ${translated.length}/${names.length} classes translated`);
}

fs.mkdirSync(path.join(OUT, 'h'), { recursive: true });
fs.mkdirSync(path.join(OUT, 'stubs'), { recursive: true });
if (!CHUNKS_ONLY) {
  fs.writeFileSync(path.join(OUT, 'game_types.h'), typesH());
  for (const m of model) if (m.kind !== 'struct') fs.writeFileSync(path.join(OUT, 'h', m.name + '.h'), hdrFor(m));
  fs.writeFileSync(path.join(OUT, 'game_all.h'), '// Generated - every game class, base classes first.\n#pragma once\n#include "game_types.h"\n' + topoOrder().filter(m => m.kind !== 'struct').map(m => `#include "h/${m.name}.h"`).join('\n') + '\n');
  for (const m of model) fs.writeFileSync(path.join(OUT, 'stubs', m.name + '.cpp'), stubFor(m));
  fs.writeFileSync(path.join(OUT, 'registry.gen.cpp'), registryCpp());
  // translator manifest
  const man = model.map(m => ({ name: m.name, file: m.file, base: m.baseName, mb: m.mb, lines: m.c.src.split('\n').length, methods: m.methods.length, needsCtor: m.needsCtor, needsCctor: m.needsCctor, props: m.props.length }));
  fs.writeFileSync(path.join(OUT, 'manifest.json'), JSON.stringify(man, null, 1));
  console.log('classes', model.length, 'monobehaviours', model.filter(m => m.mb).length, 'needing ctor', model.filter(m => m.needsCtor).length, 'needing _cctor', model.filter(m => m.needsCctor).length);
  console.log('unknown types', JSON.stringify([...unknownTypes].map(([k, v]) => k + ' (' + v.length + 'x, e.g. ' + v[0] + ')')));
}
writeChunks();
