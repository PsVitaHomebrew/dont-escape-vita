// Builds a VPK (a zip) from the staged app folder plus extra folders, e.g. the game data:
//   node tools/pack_vpk.js <out.vpk> <stageDir> [<srcDir>=<pathInVpk> ...]
//   node tools/pack_vpk.js release/1.0/DontEscape.vpk engine/out/vita/vpk data=data
// vita-pack-vpk takes one -a argument per file, and ~3,800 data files are more than a Windows command line holds.
// Already-compressed files (textures, sound, PNG) are stored as they are; the rest is deflated.
// Dot files (Mac "._" copies) are skipped.
const fs = require('fs'), path = require('path'), zlib = require('zlib');
const [out, stage, ...extra] = process.argv.slice(2);
if (!out || !stage) { console.error('usage: node pack_vpk.js <out.vpk> <stageDir> [<srcDir>=<pathInVpk> ...]'); process.exit(1); }

const table = new Uint32Array(256);
for (let n = 0; n < 256; n++) { let c = n; for (let k = 0; k < 8; k++) c = c & 1 ? 0xEDB88320 ^ (c >>> 1) : c >>> 1; table[n] = c >>> 0; }
const crc32 = b => { let c = 0xFFFFFFFF; for (let i = 0; i < b.length; i++) c = table[(c ^ b[i]) & 0xFF] ^ (c >>> 8); return (c ^ 0xFFFFFFFF) >>> 0; };

const files = [];
const walk = (dir, prefix) => {
  for (const e of fs.readdirSync(dir, { withFileTypes: true }).sort((a, b) => (a.name < b.name ? -1 : 1))) {
    if (e.name.startsWith('.')) continue;
    const p = path.join(dir, e.name), name = prefix ? prefix + '/' + e.name : e.name;
    if (e.isDirectory()) walk(p, name); else files.push({ src: p, name });
  }
};
walk(stage, '');
// eboot.bin and sce_sys/param.sfo first, the way installers expect to find them
files.sort((a, b) => (a.name === 'eboot.bin' ? -1 : b.name === 'eboot.bin' ? 1 : a.name === 'sce_sys/param.sfo' ? -1 : b.name === 'sce_sys/param.sfo' ? 1 : 0));
for (const x of extra) { const [src, dst] = x.split('='); walk(src, dst || path.basename(src)); }

const STORE = new Set(['.dtx', '.ogg', '.mp3', '.png', '.bin', '.suprx', '.self']);
const DOS_TIME = (12 << 11) | (0 << 5), DOS_DATE = ((2026 - 1980) << 9) | (10 << 5) | 30;   // fixed, so builds are repeatable
const fd = fs.openSync(out, 'w'); let offset = 0; const central = [];
const write = b => { fs.writeSync(fd, b); offset += b.length; };
for (const f of files) {
  const data = fs.readFileSync(f.src), crc = crc32(data), nameBuf = Buffer.from(f.name, 'utf8');
  let method = 0, body = data;
  if (!STORE.has(path.extname(f.name).toLowerCase())) { const d = zlib.deflateRawSync(data, { level: 9 }); if (d.length < data.length) { method = 8; body = d; } }
  const h = Buffer.alloc(30);
  h.writeUInt32LE(0x04034b50, 0); h.writeUInt16LE(20, 4); h.writeUInt16LE(0x0800, 6); h.writeUInt16LE(method, 8);
  h.writeUInt16LE(DOS_TIME, 10); h.writeUInt16LE(DOS_DATE, 12); h.writeUInt32LE(crc, 14);
  h.writeUInt32LE(body.length, 18); h.writeUInt32LE(data.length, 22); h.writeUInt16LE(nameBuf.length, 26); h.writeUInt16LE(0, 28);
  central.push({ nameBuf, method, crc, csize: body.length, usize: data.length, at: offset });
  write(h); write(nameBuf); write(body);
}
const cdStart = offset;
for (const c of central) {
  const h = Buffer.alloc(46);
  h.writeUInt32LE(0x02014b50, 0); h.writeUInt16LE(20, 4); h.writeUInt16LE(20, 6); h.writeUInt16LE(0x0800, 8); h.writeUInt16LE(c.method, 10);
  h.writeUInt16LE(DOS_TIME, 12); h.writeUInt16LE(DOS_DATE, 14); h.writeUInt32LE(c.crc, 16); h.writeUInt32LE(c.csize, 20); h.writeUInt32LE(c.usize, 24);
  h.writeUInt16LE(c.nameBuf.length, 28); h.writeUInt16LE(0, 30); h.writeUInt16LE(0, 32); h.writeUInt16LE(0, 34); h.writeUInt16LE(0, 36);
  h.writeUInt32LE(0, 38); h.writeUInt32LE(c.at, 42);
  write(h); write(c.nameBuf);
}
const end = Buffer.alloc(22);
end.writeUInt32LE(0x06054b50, 0); end.writeUInt16LE(0, 4); end.writeUInt16LE(0, 6); end.writeUInt16LE(central.length, 8); end.writeUInt16LE(central.length, 10);
end.writeUInt32LE(offset - cdStart, 12); end.writeUInt32LE(cdStart, 16); end.writeUInt16LE(0, 20);
write(end); fs.closeSync(fd);
console.log(`${out}: ${central.length} files, ${(offset / 1048576).toFixed(1)} MB`);
