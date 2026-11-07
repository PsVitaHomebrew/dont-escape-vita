'use strict';
const fs = require('fs'), zlib = require('zlib');
const { decodePng } = require('../convert/png.js');
function crc32(buf) { let c, crc = 0xffffffff; for (let n = 0; n < buf.length; n++) { c = (crc ^ buf[n]) & 0xff; for (let k = 0; k < 8; k++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1; crc = (crc >>> 8) ^ c; } return (crc ^ 0xffffffff) >>> 0; }
function chunk(type, data) { const len = Buffer.alloc(4); len.writeUInt32BE(data.length); const td = Buffer.concat([Buffer.from(type, 'latin1'), data]); const c = Buffer.alloc(4); c.writeUInt32BE(crc32(td)); return Buffer.concat([len, td, c]); }
function pngRGBA(img) { const { w, h, rgba } = img; const hdr = Buffer.alloc(13); hdr.writeUInt32BE(w, 0); hdr.writeUInt32BE(h, 4); hdr[8] = 8; hdr[9] = 6;
  const raw = Buffer.alloc((w * 4 + 1) * h); for (let y = 0; y < h; y++) { raw[y * (w * 4 + 1)] = 0; rgba.copy(raw, y * (w * 4 + 1) + 1, y * w * 4, (y + 1) * w * 4); }
  return Buffer.concat([Buffer.from([0x89, 0x50, 0x4e, 0x47, 13, 10, 26, 10]), chunk('IHDR', hdr), chunk('IDAT', zlib.deflateSync(raw, { level: 9 })), chunk('IEND', Buffer.alloc(0))]); }
const load = p => decodePng(fs.readFileSync(p));
const make = (w, h, c = [0, 0, 0, 255]) => { const rgba = Buffer.alloc(w * h * 4); for (let i = 0; i < w * h; i++) rgba.set(c, i * 4); return { w, h, rgba }; };
function scale(img, s) { const o = make(img.w * s, img.h * s); for (let y = 0; y < o.h; y++) for (let x = 0; x < o.w; x++) img.rgba.copy(o.rgba, (y * o.w + x) * 4, ((Math.floor(y / s)) * img.w + Math.floor(x / s)) * 4, ((Math.floor(y / s)) * img.w + Math.floor(x / s)) * 4 + 4); return o; }
// alpha-blit src onto dst at (dx,dy)
function blit(dst, src, dx, dy) { for (let y = 0; y < src.h; y++) for (let x = 0; x < src.w; x++) { const X = x + dx, Y = y + dy; if (X < 0 || Y < 0 || X >= dst.w || Y >= dst.h) continue; const s = (y * src.w + x) * 4, d = (Y * dst.w + X) * 4, a = src.rgba[s + 3] / 255; for (let k = 0; k < 3; k++) dst.rgba[d + k] = Math.round(src.rgba[s + k] * a + dst.rgba[d + k] * (1 - a)); dst.rgba[d + 3] = Math.max(dst.rgba[d + 3], src.rgba[s + 3]); } }
module.exports = { load, make, scale, blit, pngRGBA, chunk, crc32, decodePng };
