// Converts an AssetRipper export of Don't Escape: 4 Days in a Wasteland into compact data for the Vita engine.
// Usage: node convert.js <ExportedProject folder> <output data folder> [--skip-textures] [--skip-audio]
'use strict';
const fs = require('fs');
const path = require('path');
const zlib = require('zlib');
const { parseUnityYaml } = require('./unityyaml');
const { decodePng } = require('./png');

const SRC = path.resolve(process.argv[2]);
const OUT = path.resolve(process.argv[3]);
const SKIP_TEX = process.argv.includes('--skip-textures');
const SKIP_AUDIO = process.argv.includes('--skip-audio');
const ASSETS = path.join(SRC, 'Assets');
const stats = { unresolvedRefs: 0, unresolvedSamples: new Set(), rotated: 0, unknownClasses: {}, warnings: [] };

function walk(dir, out = []) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    if (e.name.startsWith('.')) continue; // skip dot files (e.g. Mac ._ files)
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p, out); else out.push(p);
  }
  return out;
}
const rel = p => path.relative(ASSETS, p).split(path.sep).join('/');
const mkdir = d => fs.mkdirSync(d, { recursive: true });
const num = v => { if (v === undefined || v === '') return 0; if (v === 'Infinity') return 1e30; if (v === '-Infinity') return -1e30; const n = parseFloat(v); return isNaN(n) ? 0 : n; };
const r6 = v => Math.round(num(v) * 1e6) / 1e6;
const v3 = o => [r6(o && o.x), r6(o && o.y), r6(o && o.z)];
const col = o => [r6(o && o.r), r6(o && o.g), r6(o && o.b), r6(o && o.a)];

// ---------------------------------------------------------------- 1. index every asset by GUID
const files = walk(ASSETS);
const guidToPath = new Map();
for (const f of files) {
  if (!f.endsWith('.meta')) continue;
  const m = fs.readFileSync(f, 'utf8').match(/^guid: ([0-9a-f]{32})/m);
  if (m) guidToPath.set(m[1], f.slice(0, -5));
}

const assets = [];               // global asset table
const refIndex = new Map();      // "guid:fileID" -> asset index
const byKind = { tex: [], sprite: [], audio: [], text: [], anim: [], ctrl: [], prefab: [], font: [], mat: [], script: [] };
function addAsset(kind, name, file, guid, fileID, extra = {}) {
  const idx = assets.length;
  const a = { k: kind, n: name, path: rel(file), guid, fileID: String(fileID), ...extra };
  assets.push(a); refIndex.set(guid + ':' + fileID, idx);
  a.ki = byKind[kind].length; byKind[kind].push(idx);
  return idx;
}
const scriptClass = new Map(); // guid -> class name
const sceneFiles = [];

for (const [guid, f] of guidToPath) {
  if (!fs.existsSync(f) || fs.statSync(f).isDirectory()) continue;
  const ext = path.extname(f).toLowerCase();
  const base = path.basename(f, path.extname(f));
  if (ext === '.png') addAsset('tex', base, f, guid, 2800000);
  else if (ext === '.cs') { scriptClass.set(guid, base); addAsset('script', base, f, guid, 11500000); }
  else if (ext === '.ogg') addAsset('audio', base, f, guid, 8300000, { fmt: 'ogg' });
  else if (ext === '.audioclip') addAsset('audio', base, f, guid, 8300000, { fmt: 'mp3' });
  else if (ext === '.txt') addAsset('text', base, f, guid, 4900000);
  else if (ext === '.anim') addAsset('anim', base, f, guid, 7400000);
  else if (ext === '.controller') addAsset('ctrl', base, f, guid, 9100000);
  else if (ext === '.prefab') addAsset('prefab', base, f, guid, 100100000);
  else if (ext === '.ttf' || ext === '.otf') addAsset('font', base, f, guid, 12800000);
  else if (ext === '.mat') addAsset('mat', base, f, guid, 2100000);
  else if (ext === '.unity') sceneFiles.push({ guid, f });
  else if (ext === '.asset') {
    const head = fs.readFileSync(f, 'utf8').slice(0, 300);
    const m = head.match(/--- !u!(\d+) &(-?\d+)/);
    if (!m) continue;
    const cls = +m[1];
    if (cls === 213) addAsset('sprite', base, f, guid, m[2]);
    else if (cls === 28) addAsset('tex', base, f, guid, m[2], { yamlTex: true });
    else if (cls === 49) addAsset('text', base, f, guid, m[2], { yamlText: true });
    else if (cls === 128) addAsset('font', base, f, guid, m[2]);
    else stats.unknownClasses['asset' + cls] = (stats.unknownClasses['asset' + cls] || 0) + 1;
  }
}

// prefab-internal references resolve to {a: prefabIdx, f: fileID}
const prefabGuid = new Map(byKind.prefab.map(i => [assets[i].guid, i]));

function ref(v) {
  if (!v || typeof v !== 'object' || v.fileID === undefined) return undefined;
  const fid = v.fileID;
  if (fid === '0' || fid === 0) return null;
  if (!v.guid) return { r: Number(fid) };
  const k = refIndex.get(v.guid + ':' + fid);
  if (k !== undefined) return { a: k };
  if (prefabGuid.has(v.guid)) return { a: prefabGuid.get(v.guid), f: Number(fid) };
  // A texture referenced by any fileID, or an asset whose main fileID differs
  const p = guidToPath.get(v.guid);
  if (p) { const any = assets.findIndex(a => a.guid === v.guid); if (any >= 0) return { a: any }; }
  if (v.guid === '0000000000000000f000000000000000' || v.guid === '0000000000000000e000000000000000') return { b: Number(fid) }; // Unity built-in
  stats.unresolvedRefs++; if (stats.unresolvedSamples.size < 12) stats.unresolvedSamples.add(v.guid + ':' + fid + ' (' + (p ? rel(p) : 'no file') + ')');
  return null;
}

// Script fields: keep scalars as strings, turn references into {r}/{a}/{b}/null
function fieldValue(v) {
  if (v === null || v === undefined) return '';
  if (Array.isArray(v)) return v.map(fieldValue);
  if (typeof v === 'object') {
    if ('fileID' in v && Object.keys(v).every(k => ['fileID', 'guid', 'type'].includes(k))) return ref(v);
    const o = {}; for (const [k, x] of Object.entries(v)) o[k] = fieldValue(x); return o;
  }
  return v;
}

// ---------------------------------------------------------------- 2. textures
mkdir(path.join(OUT, 'tex'));
const texJson = [];
let texBytes = 0;
const t0 = Date.now();
for (const idx of byKind.tex) {
  const a = assets[idx];
  const file = path.join(ASSETS, a.path);
  const meta = fs.existsSync(file + '.meta') ? fs.readFileSync(file + '.meta', 'utf8') : '';
  const fm = (meta.match(/filterMode: (\d+)/) || [])[1];
  const entry = { n: a.n, src: 'export/ExportedProject/Assets/' + a.path, fm: fm === undefined ? 0 : +fm };
  if (a.yamlTex) { stats.warnings.push('yaml texture not converted: ' + a.path); entry.w = entry.h = 0; texJson.push(entry); continue; }
  const png = fs.readFileSync(file);
  entry.w = png.readUInt32BE(16); entry.h = png.readUInt32BE(20);
  const outFile = path.join(OUT, 'tex', a.ki + '.dtx');
  if (!SKIP_TEX) {
    const img = decodePng(png);
    const z = zlib.deflateSync(img.rgba, { level: 6 });
    const hdr = Buffer.alloc(16);
    hdr.write('DTX1', 0, 'latin1'); hdr.writeUInt32LE(img.w, 4); hdr.writeUInt32LE(img.h, 8); hdr.writeUInt32LE(img.rgba.length, 12);
    fs.writeFileSync(outFile, Buffer.concat([hdr, z]));
    texBytes += 16 + z.length;
  }
  texJson.push(entry);
}
console.log('textures', texJson.length, (texBytes / 1048576).toFixed(1) + ' MB', ((Date.now() - t0) / 1000).toFixed(1) + 's');

// ---------------------------------------------------------------- 3. sprites
const spriteJson = [];
for (const idx of byKind.sprite) {
  const a = assets[idx];
  const doc = parseUnityYaml(fs.readFileSync(path.join(ASSETS, a.path), 'utf8'))[0].body;
  const R = doc.m_Rect, P = doc.m_Pivot, RD = doc.m_RD || {};
  const tr = ref(RD.texture);
  const e = { n: doc.m_Name || a.n, t: tr && tr.a !== undefined ? assets[tr.a].ki : -1, r: [num(R.x), num(R.y), num(R.width), num(R.height)], p: [r6(P.x), r6(P.y)], u: num(doc.m_PixelsToUnits) };
  const TR = RD.textureRect;
  if (TR && (num(TR.x) !== e.r[0] || num(TR.y) !== e.r[1] || num(TR.width) !== e.r[2] || num(TR.height) !== e.r[3])) {
    e.tr = [num(TR.x), num(TR.y), num(TR.width), num(TR.height)]; e.to = [num(RD.textureRectOffset && RD.textureRectOffset.x), num(RD.textureRectOffset && RD.textureRectOffset.y)];
  }
  if (e.t < 0) stats.warnings.push('sprite without texture: ' + a.path);
  spriteJson.push(e);
}
console.log('sprites', spriteJson.length);

// ---------------------------------------------------------------- 4. audio
mkdir(path.join(OUT, 'snd'));
const audioJson = [];
function oggInfo(b) {
  const id = b.indexOf(Buffer.from('\x01vorbis', 'latin1'));
  const ch = b[id + 11], hz = b.readUInt32LE(id + 12);
  const last = b.lastIndexOf(Buffer.from('OggS', 'latin1'));
  const gran = Number(b.readBigInt64LE(last + 6));
  return { ch, hz, len: gran / hz };
}
for (const idx of byKind.audio) {
  const a = assets[idx];
  const file = path.join(ASSETS, a.path);
  const e = { n: a.n, f: a.fmt };
  if (a.fmt === 'ogg') {
    const b = fs.readFileSync(file); Object.assign(e, oggInfo(b));
    if (!SKIP_AUDIO) fs.writeFileSync(path.join(OUT, 'snd', a.ki + '.ogg'), b);
  } else {
    const doc = parseUnityYaml(fs.readFileSync(file, 'utf8'))[0].body;
    e.ch = num(doc.m_Channels); e.hz = num(doc.m_Frequency); e.len = num(doc.m_Length); if (doc.m_Name) e.n = doc.m_Name;
    const res = file + '.resS';
    const b = fs.readFileSync(res);
    const head = b.slice(0, 3).toString('latin1');
    if (head !== 'ID3' && !(b[0] === 0xff && (b[1] & 0xe0) === 0xe0)) { stats.warnings.push('audio not mp3: ' + a.path + ' ' + head); e.f = 'raw'; }
    if (!SKIP_AUDIO) fs.writeFileSync(path.join(OUT, 'snd', a.ki + '.' + e.f), b);
  }
  e.len = Math.round(e.len * 1e4) / 1e4;
  audioJson.push(e);
}
console.log('audio', audioJson.length);

// ---------------------------------------------------------------- 5. text assets
mkdir(path.join(OUT, 'text'));
const textJson = [];
for (const idx of byKind.text) {
  const a = assets[idx];
  let content = fs.readFileSync(path.join(ASSETS, a.path));
  if (a.yamlText) { const doc = parseUnityYaml(content.toString('utf8'))[0].body; content = Buffer.from(doc.m_Script || '', 'utf8'); }
  fs.writeFileSync(path.join(OUT, 'text', a.ki + '.txt'), content);
  textJson.push({ n: a.n });
}

// ---------------------------------------------------------------- 6. animation clips
const spriteKi = r => (r && r.a !== undefined && assets[r.a].k === 'sprite') ? assets[r.a].ki : -1;
const animJson = [];
for (const idx of byKind.anim) {
  const a = assets[idx];
  const d = parseUnityYaml(fs.readFileSync(path.join(ASSETS, a.path), 'utf8'))[0].body;
  const s = d.m_AnimationClipSettings || {};
  const e = { n: d.m_Name || a.n, len: r6(num(s.m_StopTime) - num(s.m_StartTime)), rate: num(d.m_SampleRate), loop: s.m_LoopTime === '1' ? 1 : 0, pp: [], fc: [], ev: [] };
  for (const c of (Array.isArray(d.m_PPtrCurves) ? d.m_PPtrCurves : [])) {
    e.pp.push({ path: c.path || '', attr: c.attribute, k: (c.curve || []).map(k => [r6(k.time), spriteKi(ref(k.value))]) });
  }
  for (const c of (Array.isArray(d.m_FloatCurves) ? d.m_FloatCurves : [])) {
    const keys = ((c.curve && c.curve.m_Curve) || []).map(k => [r6(k.time), r6(k.value), r6(k.inSlope), r6(k.outSlope)]);
    e.fc.push({ path: c.path || '', attr: c.attribute, cls: num(c.classID), k: keys });
  }
  for (const v of (Array.isArray(d.m_Events) ? d.m_Events : [])) {
    e.ev.push({ t: r6(v.time), fn: v.functionName, s: v.data || '', f: r6(v.floatParameter), i: num(v.intParameter) });
  }
  for (const k of ['m_PositionCurves', 'm_EulerCurves', 'm_ScaleCurves', 'm_RotationCurves']) if (Array.isArray(d[k]) && d[k].length) stats.warnings.push('clip uses ' + k + ': ' + a.n);
  animJson.push(e);
}
console.log('anims', animJson.length);

// ---------------------------------------------------------------- 7. animator controllers
const ctrlJson = [];
for (const idx of byKind.ctrl) {
  const a = assets[idx];
  const docs = parseUnityYaml(fs.readFileSync(path.join(ASSETS, a.path), 'utf8'));
  const byId = new Map(docs.map(d => [d.fileID, d]));
  const ctrl = docs.find(d => d.classID === 91).body;
  const layers = [];
  for (const L of (Array.isArray(ctrl.m_AnimatorLayers) ? ctrl.m_AnimatorLayers : [])) {
    const states = []; const stateIdx = new Map(); const anyTr = [];
    const collect = (smId) => {
      const sm = byId.get(String(smId)); if (!sm) return;
      for (const cs of (Array.isArray(sm.body.m_ChildStates) ? sm.body.m_ChildStates : [])) { const sid = cs.m_State.fileID; if (!stateIdx.has(sid)) { stateIdx.set(sid, states.length); states.push(sid); } }
      for (const t of (Array.isArray(sm.body.m_AnyStateTransitions) ? sm.body.m_AnyStateTransitions : [])) anyTr.push(t.fileID);
      for (const c of (Array.isArray(sm.body.m_ChildStateMachines) ? sm.body.m_ChildStateMachines : [])) collect(c.m_StateMachine.fileID);
    };
    const rootSm = byId.get(String(L.m_StateMachine.fileID));
    collect(L.m_StateMachine.fileID);
    const tr = (tid) => {
      const t = byId.get(String(tid)); if (!t) return null; const b = t.body;
      const to = b.m_IsExit === '1' ? -1 : (stateIdx.has(b.m_DstState && b.m_DstState.fileID) ? stateIdx.get(b.m_DstState.fileID) : -1);
      return { to, he: b.m_HasExitTime === '1' ? 1 : 0, et: r6(b.m_ExitTime), d: r6(b.m_TransitionDuration), c: Array.isArray(b.m_Conditions) ? b.m_Conditions.length : 0, mute: b.m_Mute === '1' ? 1 : 0 };
    };
    const out = states.map(sid => {
      const s = byId.get(String(sid)).body; const m = ref(s.m_Motion);
      return { n: s.m_Name, clip: m && m.a !== undefined && assets[m.a].k === 'anim' ? assets[m.a].ki : -1, sp: num(s.m_Speed) || 1, co: r6(s.m_CycleOffset), tr: (Array.isArray(s.m_Transitions) ? s.m_Transitions : []).map(t => tr(t.fileID)).filter(Boolean) };
    });
    const def = rootSm && stateIdx.has(rootSm.body.m_DefaultState && rootSm.body.m_DefaultState.fileID) ? stateIdx.get(rootSm.body.m_DefaultState.fileID) : 0;
    layers.push({ n: L.m_Name, def, states: out, any: anyTr.map(tr).filter(Boolean) });
  }
  ctrlJson.push({ n: ctrl.m_Name || a.n, layers });
}
console.log('controllers', ctrlJson.length);

// ---------------------------------------------------------------- 8. scenes and prefabs
function convertObjects(docs, label) {
  const byId = new Map(docs.map(d => [d.fileID, d]));
  const objs = [];
  for (const d of docs) {
    if (d.classID !== 1) continue;
    const g = d.body;
    const o = { id: Number(d.fileID), n: g.m_Name || '', l: num(g.m_Layer), tag: g.m_TagString || 'Untagged', a: g.m_IsActive === '0' ? 0 : 1, c: [] };
    for (const cr of (Array.isArray(g.m_Component) ? g.m_Component : [])) {
      const cid = cr.component ? cr.component.fileID : (cr['114'] || cr['4'] || {}).fileID; // older formats keyed by class id
      const cd = byId.get(String(cid));
      if (!cd) continue;
      const b = cd.body; const en = b.m_Enabled === '0' ? 0 : 1;
      const base = { id: Number(cd.fileID) };
      switch (cd.classID) {
        case 4: {
          const q = b.m_LocalRotation || {}; const rot = [r6(q.x), r6(q.y), r6(q.z), r6(q.w === undefined ? 1 : q.w)];
          o.p = v3(b.m_LocalPosition); o.s = v3(b.m_LocalScale);
          if (rot[0] || rot[1] || rot[2] || rot[3] !== 1) { o.q = rot; stats.rotated++; }
          o.tid = Number(cd.fileID);
          o.father = b.m_Father && b.m_Father.fileID !== '0' ? Number(b.m_Father.fileID) : 0;
          o.kids = (Array.isArray(b.m_Children) ? b.m_Children : []).map(x => Number(x.fileID));
          o.ro = num(b.m_RootOrder);
          continue;
        }
        case 212: o.c.push({ ...base, k: 'sr', en, sp: ref(b.m_Sprite), col: col(b.m_Color), fx: +b.m_FlipX || 0, fy: +b.m_FlipY || 0, sl: num(b.m_SortingLayerID), so: num(b.m_SortingOrder), mi: num(b.m_MaskInteraction), dm: num(b.m_DrawMode), sz: [r6(b.m_Size && b.m_Size.x), r6(b.m_Size && b.m_Size.y)], mat: ref((b.m_Materials || [])[0]) }); break;
        case 61: o.c.push({ ...base, k: 'box', en, tr: +b.m_IsTrigger || 0, off: [r6(b.m_Offset.x), r6(b.m_Offset.y)], sz: [r6(b.m_Size.x), r6(b.m_Size.y)] }); break;
        case 58: o.c.push({ ...base, k: 'circle', en, tr: +b.m_IsTrigger || 0, off: [r6(b.m_Offset.x), r6(b.m_Offset.y)], rad: r6(b.m_Radius) }); break;
        case 60: {
          const paths = ((b.m_Points && b.m_Points.m_Paths) || []).map(p => (Array.isArray(p) ? p : []).flatMap(pt => [r6(pt.x), r6(pt.y)]));
          o.c.push({ ...base, k: 'poly', en, tr: +b.m_IsTrigger || 0, off: [r6(b.m_Offset.x), r6(b.m_Offset.y)], paths }); break;
        }
        case 95: { const c = ref(b.m_Controller); o.c.push({ ...base, k: 'animator', en, ctrl: c && c.a !== undefined && assets[c.a].k === 'ctrl' ? assets[c.a].ki : -1 }); break; }
        case 82: {
          const c = ref(b.m_audioClip);
          o.c.push({ ...base, k: 'audio', en, clip: c && c.a !== undefined && assets[c.a].k === 'audio' ? assets[c.a].ki : -1, vol: r6(b.m_Volume), pitch: r6(b.m_Pitch), loop: +b.Loop || 0, poa: +b.m_PlayOnAwake || 0, mute: +b.Mute || 0, pan: r6(b.Pan2D), prio: num(b.Priority) });
          break;
        }
        case 164: o.c.push({ ...base, k: 'reverb', en, preset: num(b.m_ReverbPreset) }); break;
        case 81: o.c.push({ ...base, k: 'listener', en }); break;
        case 20: {
          const vr = b.m_NormalizedViewPortRect || {};
          o.c.push({ ...base, k: 'camera', en, ortho: +b.orthographic || 0, os: r6(b['orthographic size']), depth: num(b.m_Depth), mask: num(b.m_CullingMask && b.m_CullingMask.m_Bits), clear: num(b.m_ClearFlags), bg: col(b.m_BackGroundColor), rect: [r6(vr.x), r6(vr.y), r6(vr.width), r6(vr.height)], near: r6(b['near clip plane']), far: r6(b['far clip plane']), tt: ref(b.m_TargetTexture) });
          break;
        }
        case 331: o.c.push({ ...base, k: 'mask', en, sp: ref(b.m_Sprite), cut: r6(b.m_MaskAlphaCutoff), front: num(b.m_FrontSortingOrder), back: num(b.m_BackSortingOrder), custom: +b.m_IsCustomRangeActive || 0 }); break;
        case 114: {
          const scr = b.m_Script || {};
          const cls = scriptClass.get(scr.guid) || ('?' + scr.guid);
          if (cls.startsWith('?')) stats.warnings.push(label + ': unknown script ' + scr.guid);
          const f = {};
          for (const [k, v] of Object.entries(b)) { if (k.startsWith('m_')) continue; f[k] = fieldValue(v); }
          o.c.push({ ...base, k: 'mb', en, cls, f });
          break;
        }
        case 92: case 124: o.c.push({ ...base, k: cd.classID === 92 ? 'guilayer' : 'flare', en }); break;
        default: stats.unknownClasses['comp' + cd.classID] = (stats.unknownClasses['comp' + cd.classID] || 0) + 1; o.c.push({ ...base, k: 'unknown' + cd.classID, en });
      }
    }
    objs.push(o);
  }
  // parent / children as GameObject ids
  const goByTransform = new Map(objs.map(o => [o.tid, o.id]));
  for (const o of objs) {
    o.parent = o.father ? (goByTransform.get(o.father) || 0) : 0;
    o.ch = (o.kids || []).map(t => goByTransform.get(t)).filter(Boolean);
    delete o.father; delete o.kids; delete o.tid;
  }
  // order roots by RootOrder
  return objs;
}

mkdir(path.join(OUT, 'scenes'));
const buildSettings = fs.readFileSync(path.join(SRC, 'ProjectSettings', 'EditorBuildSettings.asset'), 'utf8');
const buildPaths = [...buildSettings.matchAll(/path: (.+)/g)].map(m => m[1].trim());
const sceneList = [];
for (let i = 0; i < buildPaths.length; i++) {
  const f = path.join(SRC, buildPaths[i]);
  const docs = parseUnityYaml(fs.readFileSync(f, 'utf8'));
  const objs = convertObjects(docs, buildPaths[i]);
  const name = path.basename(f, '.unity');
  fs.writeFileSync(path.join(OUT, 'scenes', i + '.json'), JSON.stringify({ name, objs }));
  sceneList.push(name);
}
console.log('scenes', sceneList.length);

mkdir(path.join(OUT, 'prefabs'));
const prefabJson = [];
for (const idx of byKind.prefab) {
  const a = assets[idx];
  const docs = parseUnityYaml(fs.readFileSync(path.join(ASSETS, a.path), 'utf8'));
  const objs = convertObjects(docs, a.path);
  const root = objs.find(o => !o.parent);
  fs.writeFileSync(path.join(OUT, 'prefabs', a.ki + '.json'), JSON.stringify({ name: a.n, root: root ? root.id : 0, objs }));
  prefabJson.push({ n: a.n, root: root ? root.id : 0 });
}
console.log('prefabs', prefabJson.length);

// ---------------------------------------------------------------- 9. Resources.Load index and manifest
const resources = {};
for (const a of assets) {
  if (!a.path.startsWith('Resources/') || a.k === 'script') continue;
  const p = a.path.slice('Resources/'.length).replace(/\.[^./]+$/, '');
  (resources[p] = resources[p] || []).push([a.k, a.ki]);
}
// Sprites cut from a texture are sub-assets of it in Unity: Resources.Load/LoadAll on the texture's path return them.
const natural = (a, b) => a.localeCompare(b, undefined, { numeric: true, sensitivity: 'base' });
const texResPath = new Map();
for (const idx of byKind.tex) { const a = assets[idx]; if (a.path.startsWith('Resources/')) texResPath.set(a.ki, a.path.slice('Resources/'.length).replace(/\.[^./]+$/, '')); }
let subAssets = 0;
spriteJson.forEach((sp, ki) => {
  const p = texResPath.get(sp.t); if (!p) return;
  const list = (resources[p] = resources[p] || []);
  if (!list.some(e => e[0] === 'sprite' && e[1] === ki)) { list.push(['sprite', ki]); subAssets++; }
});
for (const p of Object.keys(resources)) {
  const list = resources[p];
  const other = list.filter(e => e[0] !== 'sprite'), spr = list.filter(e => e[0] === 'sprite');
  spr.sort((x, y) => natural(spriteJson[x[1]].n, spriteJson[y[1]].n));
  resources[p] = other.concat(spr);
}
console.log('sprite sub-assets registered under their texture path:', subAssets);
const tagMgr = fs.readFileSync(path.join(SRC, 'ProjectSettings', 'TagManager.asset'), 'utf8');
const tm = parseUnityYaml(tagMgr)[0].body;
const manifest = {
  version: 1,
  scenes: sceneList,
  tags: tm.tags || [],
  layers: tm.layers || [],
  sortingLayers: (tm.m_SortingLayers || []).map(s => ({ n: s.name, id: num(s.uniqueID) })),
  counts: { tex: texJson.length, sprite: spriteJson.length, audio: audioJson.length, text: textJson.length, anim: animJson.length, ctrl: ctrlJson.length, prefab: prefabJson.length },
};
const W = (n, o) => fs.writeFileSync(path.join(OUT, n), JSON.stringify(o));
W('manifest.json', manifest); W('textures.json', texJson); W('sprites.json', spriteJson); W('audio.json', audioJson);
W('texts.json', textJson); W('anims.json', animJson); W('controllers.json', ctrlJson); W('prefabs.json', prefabJson); W('resources.json', resources);
// global asset index -> [kind, index within kind]; scene/prefab refs {a: N} use the global index
W('assetindex.json', { ...byKind, all: assets.map(a => [a.k, a.ki, a.n]) });

stats.unresolvedSamples = [...stats.unresolvedSamples];
console.log('STATS', JSON.stringify({ ...stats, warnings: stats.warnings.slice(0, 20), warningCount: stats.warnings.length }, null, 1));
