// Writes the LiveArea art into a sce_sys folder: icon0.png, bg.png and startup.png are copied from ./art when present,
// otherwise simple original placeholders are drawn (8-bit palette PNGs: a dark sky, a sand line and a doorway).
// Usage: node make_art.js <out sce_sys folder>
'use strict';
const fs = require('fs'), path = require('path'), zlib = require('zlib');
const out = path.resolve(process.argv[2]);
fs.mkdirSync(path.join(out, 'livearea', 'contents'), { recursive: true });

const PAL = [[18, 20, 32], [38, 42, 64], [196, 152, 92], [140, 104, 62], [240, 196, 120], [10, 10, 14], [92, 70, 46]];
function crc32(buf) { let c, crc = 0xffffffff; for (let n = 0; n < buf.length; n++) { c = (crc ^ buf[n]) & 0xff; for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1; crc = (crc >>> 8) ^ c; } return (crc ^ 0xffffffff) >>> 0; }
function chunk(type, data) { const len = Buffer.alloc(4); len.writeUInt32BE(data.length); const td = Buffer.concat([Buffer.from(type, 'latin1'), data]); const c = Buffer.alloc(4); c.writeUInt32BE(crc32(td)); return Buffer.concat([len, td, c]); }
function png(w, h, px) {
  const hdr = Buffer.alloc(13); hdr.writeUInt32BE(w, 0); hdr.writeUInt32BE(h, 4); hdr[8] = 8; hdr[9] = 3;
  const raw = Buffer.alloc((w + 1) * h); for (let y = 0; y < h; y++) { raw[y * (w + 1)] = 0; for (let x = 0; x < w; x++) raw[y * (w + 1) + 1 + x] = px(x, y); }
  return Buffer.concat([Buffer.from([0x89, 0x50, 0x4e, 0x47, 13, 10, 26, 10]), chunk('IHDR', hdr), chunk('PLTE', Buffer.from(PAL.flat())), chunk('IDAT', zlib.deflateSync(raw, { level: 9 })), chunk('IEND', Buffer.alloc(0))]);
}
// scene drawn on a coarse pixel grid so it reads as pixel art
function scene(w, h, cell) {
  return (x, y) => {
    const gx = Math.floor(x / cell), gy = Math.floor(y / cell), GW = Math.ceil(w / cell), GH = Math.ceil(h / cell);
    const horizon = Math.floor(GH * 0.68);
    const dw = Math.max(3, Math.floor(GW * 0.16)), dh = Math.max(5, Math.floor(GH * 0.42));
    const dx0 = Math.floor(GW / 2 - dw / 2), dy0 = horizon - dh;
    if (gx >= dx0 - 1 && gx <= dx0 + dw && gy >= dy0 - 1 && gy < horizon) {
      if (gx === dx0 - 1 || gx === dx0 + dw || gy === dy0 - 1) return 6;          // frame
      return gy > dy0 + 1 ? 4 : 2;                                               // lit doorway
    }
    if (gy >= horizon) return ((gx * 7 + gy * 3) % 11 === 0) ? 3 : 2;            // sand
    if (gy === horizon - 1) return 3;
    return ((gx * 13 + gy * 17) % 37 === 0 && gy < horizon - 3) ? 4 : (gy < GH * 0.3 ? 0 : 1); // sky with a few stars
  };
}
// Real art (made from the game's own bitmaps) lives in ./art; use each file when it is there and is a valid
// 8-bit palette PNG of the right size, otherwise fall back to the placeholder for that file.
const ART = path.join(__dirname, 'art');
function artFile(name, w, h) {
  const p = path.join(ART, name);
  if (!fs.existsSync(p)) return null;
  const b = fs.readFileSync(p);
  const ok = b.length > 33 && b.readUInt32BE(0) === 0x89504e47 && b.toString('latin1', 12, 16) === 'IHDR' &&
    b.readUInt32BE(16) === w && b.readUInt32BE(20) === h && b[24] === 8 && b[25] === 3;
  if (!ok) { console.error(`make_art: ${p} is not a ${w}x${h} 8-bit palette PNG, using the placeholder`); return null; }
  return b;
}
for (const [name, dest, w, h, cell] of [
  ['icon0.png', 'icon0.png', 128, 128, 8],
  ['bg.png', 'livearea/contents/bg.png', 840, 500, 10],
  ['startup.png', 'livearea/contents/startup.png', 280, 158, 6],
]) {
  const real = artFile(name, w, h);
  fs.writeFileSync(path.join(out, dest), real || png(w, h, scene(w, h, cell)));
  console.log(name, real ? 'from art/' : 'placeholder');
}
fs.writeFileSync(path.join(out, 'livearea', 'contents', 'template.xml'),
`<?xml version="1.0" encoding="utf-8"?>
<livearea style="a1" format-ver="01.00" content-rev="1">
  <livearea-background>
    <image>bg.png</image>
  </livearea-background>
  <gate>
    <startup-image>startup.png</startup-image>
  </gate>
</livearea>
`);
console.log('art written to', out);
