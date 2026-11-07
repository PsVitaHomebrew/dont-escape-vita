// Small PNG decoder (8-bit grey, grey+alpha, RGB, RGBA and palette; no interlacing) -> RGBA8.
'use strict';
const zlib = require('zlib');

function decodePng(buf) {
  if (buf.readUInt32BE(0) !== 0x89504e47) throw new Error('not a PNG');
  let o = 8, w = 0, h = 0, depth = 0, ct = 0, inter = 0, pal = null, trns = null;
  const idat = [];
  while (o < buf.length) {
    const len = buf.readUInt32BE(o); const type = buf.toString('latin1', o + 4, o + 8); const d = buf.subarray(o + 8, o + 8 + len);
    if (type === 'IHDR') { w = d.readUInt32BE(0); h = d.readUInt32BE(4); depth = d[8]; ct = d[9]; inter = d[12]; }
    else if (type === 'PLTE') pal = d;
    else if (type === 'tRNS') trns = d;
    else if (type === 'IDAT') idat.push(d);
    else if (type === 'IEND') break;
    o += 12 + len;
  }
  if (inter) throw new Error('interlaced PNG not supported');
  const ch = { 0: 1, 2: 3, 3: 1, 4: 2, 6: 4 }[ct];
  if (!ch) throw new Error('PNG colour type ' + ct);
  const raw = zlib.inflateSync(Buffer.concat(idat));
  const bitsPP = ch * depth, bpp = Math.max(1, bitsPP >> 3), stride = (w * bitsPP + 7) >> 3;
  const px = Buffer.alloc(stride * h);
  let prev = Buffer.alloc(stride);
  for (let y = 0; y < h; y++) {
    const f = raw[y * (stride + 1)];
    const line = raw.subarray(y * (stride + 1) + 1, (y + 1) * (stride + 1));
    const out = px.subarray(y * stride, (y + 1) * stride);
    for (let x = 0; x < stride; x++) {
      const a = x >= bpp ? out[x - bpp] : 0, b = prev[x], c = x >= bpp ? prev[x - bpp] : 0;
      let v = line[x];
      if (f === 1) v += a; else if (f === 2) v += b; else if (f === 3) v += (a + b) >> 1;
      else if (f === 4) { const p = a + b - c, pa = Math.abs(p - a), pb = Math.abs(p - b), pc = Math.abs(p - c); v += pa <= pb && pa <= pc ? a : pb <= pc ? b : c; }
      out[x] = v & 255;
    }
    prev = out;
  }
  const rgba = Buffer.alloc(w * h * 4);
  const sample = (y, x, i) => { // returns 8-bit sample for channel i
    if (depth === 8) return px[y * stride + x * ch + i];
    if (depth === 16) return px[y * stride + (x * ch + i) * 2];
    const bit = (x * ch + i) * depth; const byte = px[y * stride + (bit >> 3)];
    const v = (byte >> (8 - depth - (bit & 7))) & ((1 << depth) - 1);
    return ct === 3 ? v : Math.round(v * 255 / ((1 << depth) - 1));
  };
  for (let y = 0; y < h; y++) for (let x = 0; x < w; x++) {
    const d = (y * w + x) * 4;
    if (ct === 6) { rgba[d] = sample(y, x, 0); rgba[d + 1] = sample(y, x, 1); rgba[d + 2] = sample(y, x, 2); rgba[d + 3] = sample(y, x, 3); }
    else if (ct === 2) { rgba[d] = sample(y, x, 0); rgba[d + 1] = sample(y, x, 1); rgba[d + 2] = sample(y, x, 2); rgba[d + 3] = 255; }
    else if (ct === 0) { const g = sample(y, x, 0); rgba[d] = rgba[d + 1] = rgba[d + 2] = g; rgba[d + 3] = 255; }
    else if (ct === 4) { const g = sample(y, x, 0); rgba[d] = rgba[d + 1] = rgba[d + 2] = g; rgba[d + 3] = sample(y, x, 1); }
    else { const i = sample(y, x, 0); rgba[d] = pal[i * 3]; rgba[d + 1] = pal[i * 3 + 1]; rgba[d + 2] = pal[i * 3 + 2]; rgba[d + 3] = trns && i < trns.length ? trns[i] : 255; }
  }
  return { w, h, rgba };
}
module.exports = { decodePng };
