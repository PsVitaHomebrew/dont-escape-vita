// Checks a VPK made by pack_vpk.js: every entry's name, CRC and bytes against the source folders.
//   node tools/verify_vpk.js <vpk> <stageDir> [<srcDir>=<pathInVpk> ...]
const fs = require('fs'), path = require('path'), zlib = require('zlib');
const [vpk, stage, ...extra] = process.argv.slice(2);
const buf = fs.readFileSync(vpk);
const table = new Uint32Array(256);
for (let n = 0; n < 256; n++) { let c = n; for (let k = 0; k < 8; k++) c = c & 1 ? 0xEDB88320 ^ (c >>> 1) : c >>> 1; table[n] = c >>> 0; }
const crc32 = b => { let c = 0xFFFFFFFF; for (let i = 0; i < b.length; i++) c = table[(c ^ b[i]) & 0xFF] ^ (c >>> 8); return (c ^ 0xFFFFFFFF) >>> 0; };
// where each name should come from
const map = new Map();
const walk = (dir, prefix) => { for (const e of fs.readdirSync(dir, { withFileTypes: true })) { if (e.name.startsWith('.')) continue; const p = path.join(dir, e.name), n = prefix ? prefix + '/' + e.name : e.name; if (e.isDirectory()) walk(p, n); else map.set(n, p); } };
walk(stage, ''); for (const x of extra) { const [s, d] = x.split('='); walk(s, d); }
let eocd = buf.length - 22; while (eocd >= 0 && buf.readUInt32LE(eocd) !== 0x06054b50) eocd--;
const count = buf.readUInt16LE(eocd + 10); let p = buf.readUInt32LE(eocd + 16), bad = 0; const seen = new Set();
for (let i = 0; i < count; i++) {
  const method = buf.readUInt16LE(p + 10), crc = buf.readUInt32LE(p + 16), csize = buf.readUInt32LE(p + 20), nlen = buf.readUInt16LE(p + 28), elen = buf.readUInt16LE(p + 30), clen = buf.readUInt16LE(p + 32), at = buf.readUInt32LE(p + 42);
  const name = buf.toString('utf8', p + 46, p + 46 + nlen); p += 46 + nlen + elen + clen;
  const lnl = buf.readUInt16LE(at + 26), lel = buf.readUInt16LE(at + 28), body = buf.subarray(at + 30 + lnl + lel, at + 30 + lnl + lel + csize);
  const data = method === 8 ? zlib.inflateRawSync(body) : body;
  const src = map.get(name);
  if (!src) { console.log('UNEXPECTED', name); bad++; continue; }
  seen.add(name);
  if (crc32(data) !== crc || !data.equals(fs.readFileSync(src))) { console.log('DIFFERENT', name); bad++; }
}
for (const n of map.keys()) if (!seen.has(n)) { console.log('MISSING', n); bad++; }
console.log(`${count} entries checked, ${bad} problems`);
process.exit(bad ? 1 : 0);
