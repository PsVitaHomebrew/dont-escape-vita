// Builds the Don't Escape LiveArea art from the game's own bitmaps.
// node build.js <out dir>
// Writes icon0.png (128x128), bg.png (840x500), startup.png (280x158) as 8-bit palette PNGs, plus preview.png.
'use strict';
const fs = require('fs'), path = require('path'), zlib = require('zlib');
const L = require('./lib.js');
const OUT = path.resolve(process.argv[2] || 'out');
fs.mkdirSync(OUT, { recursive: true });
const A = path.join(__dirname, '../../export/ExportedProject/Assets/Resources/bitmaps/');
const SRC = {
  menu: A + 'locations/titlescreen.png',          // main-menu skyline over the dunes, 240x135
  logo1: A + 'locations/optionsmenu/title_card.png',   // "Don't Escape", positioned for the 240x135 menu frame
  logo2: A + 'locations/optionsmenu/title_card_2.png', // "4 Days to Survive"
  dave: A + 'misc/icon_dave_big.png',              // the game's own app icon (same art as the exe icon), 768x768 = 24x24 art px of 32px
};

// ---------- image helpers (RGBA8 {w,h,rgba}) ----------
const crop = (im, x0, y0, w, h) => { const o = L.make(w, h); for (let y = 0; y < h; y++) im.rgba.copy(o.rgba, y * w * 4, ((y + y0) * im.w + x0) * 4, ((y + y0) * im.w + x0 + w) * 4); return o; };
// nearest-neighbour sample: out(X,Y) = in(clamp(floor((X-ox)/s)), clamp(floor((Y-oy)/s)))
function place(im, W, H, s, ox, oy) {
  const o = L.make(W, H);
  for (let Y = 0; Y < H; Y++) for (let X = 0; X < W; X++) {
    const x = Math.min(im.w - 1, Math.max(0, Math.floor((X - ox) / s))), y = Math.min(im.h - 1, Math.max(0, Math.floor((Y - oy) / s)));
    im.rgba.copy(o.rgba, (Y * W + X) * 4, (y * im.w + x) * 4, (y * im.w + x) * 4 + 4);
  }
  return o;
}
// shift an RGBA overlay inside its own frame
function shifted(im, dx, dy) { const o = L.make(im.w, im.h, [0, 0, 0, 0]); for (let y = 0; y < im.h; y++) for (let x = 0; x < im.w; x++) { const X = x + dx, Y = y + dy; if (X < 0 || Y < 0 || X >= im.w || Y >= im.h) continue; im.rgba.copy(o.rgba, (Y * im.w + X) * 4, (y * im.w + x) * 4, (y * im.w + x) * 4 + 4); } return o; }
function bbox(im) { let x0 = 1e9, y0 = 1e9, x1 = -1, y1 = -1; for (let y = 0; y < im.h; y++) for (let x = 0; x < im.w; x++) if (im.rgba[(y * im.w + x) * 4 + 3]) { x0 = Math.min(x0, x); y0 = Math.min(y0, y); x1 = Math.max(x1, x); y1 = Math.max(y1, y); } return { x0, y0, x1, y1 }; }

// ---------- quantizer: weighted median cut, then k-means refinement ----------
const dist = (r1, g1, b1, r2, g2, b2) => { const dr = r1 - r2, dg = g1 - g2, db = b1 - b2; return 2 * dr * dr + 4 * dg * dg + 3 * db * db; };
function quantize(im, maxC = 256) {
  const hist = new Map();
  for (let i = 0; i < im.w * im.h; i++) { const k = (im.rgba[i * 4] << 16) | (im.rgba[i * 4 + 1] << 8) | im.rgba[i * 4 + 2]; hist.set(k, (hist.get(k) || 0) + 1); }
  const cols = [...hist].map(([k, n]) => ({ r: k >> 16, g: (k >> 8) & 255, b: k & 255, n }));
  let pal;
  if (cols.length <= maxC) pal = cols.map(c => [c.r, c.g, c.b]);
  else {
    // median cut: always split the box with the largest weighted squared error, on its widest (weighted) axis,
    // at the cut that minimises the two halves' error
    const W3 = [2, 4, 3], KEYS = ['r', 'g', 'b'];
    const sse = bx => { let n = 0, s = [0, 0, 0], q = [0, 0, 0]; for (const c of bx) { n += c.n; const v = [c.r, c.g, c.b]; for (let k = 0; k < 3; k++) { s[k] += v[k] * c.n; q[k] += v[k] * v[k] * c.n; } } const vr = [0, 1, 2].map(k => W3[k] * (q[k] - s[k] * s[k] / n)); return { n, e: vr[0] + vr[1] + vr[2], vr }; };
    let boxes = [{ c: cols, ...sse(cols) }];
    while (boxes.length < maxC) {
      let best = -1, be = 0; boxes.forEach((b, i) => { if (b.c.length > 1 && b.e > be) { be = b.e; best = i; } });
      if (best < 0) break;
      const b = boxes[best], ax = b.vr.indexOf(Math.max(...b.vr)), key = KEYS[ax];
      b.c.sort((p, q) => p[key] - q[key]);
      // prefix sums along the axis to find the split with the smallest total error on that axis
      let n = 0, s = 0, q = 0; const N = b.n, S = b.c.reduce((a, c) => a + c[key] * c.n, 0), Q = b.c.reduce((a, c) => a + c[key] * c[key] * c.n, 0);
      let cut = 1, bestE = Infinity;
      for (let i = 0; i < b.c.length - 1; i++) { const c = b.c[i]; n += c.n; s += c[key] * c.n; q += c[key] * c[key] * c.n; if (b.c[i + 1][key] === c[key]) continue; const e = (q - s * s / n) + ((Q - q) - (S - s) * (S - s) / (N - n)); if (e < bestE) { bestE = e; cut = i + 1; } }
      const A1 = b.c.slice(0, cut), A2 = b.c.slice(cut);
      boxes.splice(best, 1, { c: A1, ...sse(A1) }, { c: A2, ...sse(A2) });
    }
    pal = boxes.map(({ c: bx }) => { let n = 0, r = 0, g = 0, b = 0; for (const c of bx) { n += c.n; r += c.r * c.n; g += c.g * c.n; b += c.b * c.n; } return [r / n, g / n, b / n]; });
    for (let it = 0; it < 20; it++) { // k-means refinement over the weighted histogram
      const acc = pal.map(() => [0, 0, 0, 0]); let worst = null, wd = -1;
      for (const c of cols) { let bi = 0, bd = Infinity; for (let p = 0; p < pal.length; p++) { const d = dist(c.r, c.g, c.b, pal[p][0], pal[p][1], pal[p][2]); if (d < bd) { bd = d; bi = p; } } const a = acc[bi]; a[0] += c.r * c.n; a[1] += c.g * c.n; a[2] += c.b * c.n; a[3] += c.n; if (bd > wd) { wd = bd; worst = c; } }
      pal = pal.map((p, i) => acc[i][3] ? [acc[i][0] / acc[i][3], acc[i][1] / acc[i][3], acc[i][2] / acc[i][3]] : (worst ? [worst.r, worst.g, worst.b] : p)); // re-seed empty entries at the worst-fit colour
    }
    pal = pal.map(p => p.map(Math.round));
  }
  const lut = new Map(); let err = 0, maxErr = 0;
  for (const c of cols) { let bi = 0, bd = Infinity; for (let p = 0; p < pal.length; p++) { const d = dist(c.r, c.g, c.b, pal[p][0], pal[p][1], pal[p][2]); if (d < bd) { bd = d; bi = p; } } lut.set((c.r << 16) | (c.g << 8) | c.b, bi); const e = Math.max(Math.abs(c.r - pal[bi][0]), Math.abs(c.g - pal[bi][1]), Math.abs(c.b - pal[bi][2])); err += e * c.n; maxErr = Math.max(maxErr, e); }
  const idx = Buffer.alloc(im.w * im.h);
  for (let i = 0; i < im.w * im.h; i++) idx[i] = lut.get((im.rgba[i * 4] << 16) | (im.rgba[i * 4 + 1] << 8) | im.rgba[i * 4 + 2]);
  return { w: im.w, h: im.h, idx, pal, srcColours: cols.length, meanErr: err / (im.w * im.h), maxErr };
}
// upscale an indexed image by integer s (nearest), optional margin with edge extension handled by place() on RGBA instead
function pngIndexed(q) {
  const { w, h, idx, pal } = q;
  const hdr = Buffer.alloc(13); hdr.writeUInt32BE(w, 0); hdr.writeUInt32BE(h, 4); hdr[8] = 8; hdr[9] = 3; // 8-bit, colour type 3 (palette)
  const raw = Buffer.alloc((w + 1) * h); for (let y = 0; y < h; y++) { raw[y * (w + 1)] = 0; idx.copy(raw, y * (w + 1) + 1, y * w, (y + 1) * w); }
  return Buffer.concat([Buffer.from([0x89, 0x50, 0x4e, 0x47, 13, 10, 26, 10]), L.chunk('IHDR', hdr), L.chunk('PLTE', Buffer.from(pal.flat())), L.chunk('IDAT', zlib.deflateSync(raw, { level: 9, memLevel: 9 })), L.chunk('IEND', Buffer.alloc(0))]);
}
// quantize at art resolution, then scale the indices, so every art pixel stays one flat block
function indexedScaled(art, W, H, s, ox, oy) {
  const q = quantize(art);
  const idx = Buffer.alloc(W * H);
  for (let Y = 0; Y < H; Y++) for (let X = 0; X < W; X++) {
    const x = Math.min(art.w - 1, Math.max(0, Math.floor((X - ox) / s))), y = Math.min(art.h - 1, Math.max(0, Math.floor((Y - oy) / s)));
    idx[Y * W + X] = q.idx[y * art.w + x];
  }
  return { ...q, w: W, h: H, idx };
}
const toRGBA = q => { const o = L.make(q.w, q.h); for (let i = 0; i < q.w * q.h; i++) { const p = q.pal[q.idx[i]]; o.rgba[i * 4] = p[0]; o.rgba[i * 4 + 1] = p[1]; o.rgba[i * 4 + 2] = p[2]; } return o; };

// ---------- sources ----------
const menu = L.load(SRC.menu), logo1 = L.load(SRC.logo1), logo2 = L.load(SRC.logo2), daveBig = L.load(SRC.dave);

// icon0: the game's icon art on its native 24x24 grid, 5x nearest (120px) centred in 128, edge pixels extended 4px
const CELL = 32, dave = L.make(daveBig.w / CELL, daveBig.h / CELL);
let uneven = 0;
for (let y = 0; y < dave.h; y++) for (let x = 0; x < dave.w; x++) {
  const c = ((y * CELL + 16) * daveBig.w + x * CELL + 16) * 4; daveBig.rgba.copy(dave.rgba, (y * dave.w + x) * 4, c, c + 4);
  for (let yy = 0; yy < CELL; yy++) for (let xx = 0; xx < CELL; xx++) { const p = ((y * CELL + yy) * daveBig.w + x * CELL + xx) * 4; if (daveBig.rgba.readUInt32BE(p) !== daveBig.rgba.readUInt32BE(c)) uneven++; }
}
const icon = indexedScaled(dave, 128, 128, 5, 4, 4);

// bg: menu art, 4x nearest, crop 210x125 art px -> 840x500
const BG = { ox: +(process.env.BGX || 6), oy: +(process.env.BGY || 3) };
const bg = indexedScaled(crop(menu, BG.ox, BG.oy, 210, 125), 840, 500, 4, 0, 0);

// startup: menu art + logo, 2x nearest, crop 140x79 art px -> 280x158, logo centred horizontally
const ST = { ox: +(process.env.STX || 8), oy: +(process.env.STY || 10), logoY: +(process.env.LOGOY || 35) };
const comp = L.make(240, 135); L.blit(comp, menu, 0, 0);
const lb = (() => { const a = bbox(logo1), b = bbox(logo2); return { x0: Math.min(a.x0, b.x0), y0: Math.min(a.y0, b.y0), x1: Math.max(a.x1, b.x1), y1: Math.max(a.y1, b.y1) }; })();
const ldx = ST.ox + Math.round((140 - (lb.x1 - lb.x0 + 1)) / 2) - lb.x0, ldy = ST.oy + ST.logoY - lb.y0;
L.blit(comp, shifted(logo1, ldx, ldy), 0, 0); L.blit(comp, shifted(logo2, ldx, ldy), 0, 0);
const startup = indexedScaled(crop(comp, ST.ox, ST.oy, 140, 79), 280, 158, 2, 0, 0);

const files = { 'icon0.png': icon, 'bg.png': bg, 'startup.png': startup };
for (const [n, q] of Object.entries(files)) {
  const buf = pngIndexed(q); fs.writeFileSync(path.join(OUT, n), buf);
  console.log(n.padEnd(12), `${q.w}x${q.h}`, `${buf.length} bytes`, `palette ${q.pal.length}`, `src colours ${q.srcColours}`, `mean err ${q.meanErr.toFixed(2)} max ${q.maxErr}`);
}
console.log('icon cells non-uniform px:', uneven, ' logo bbox', lb, 'shift', ldx, ldy);

// ---------- preview: bg | startup | icon | icon in a circle, on a dark panel ----------
{
  const back = L.load(path.join(OUT, 'bg.png')), st = L.load(path.join(OUT, 'startup.png')), ic = L.load(path.join(OUT, 'icon0.png'));
  const PAD = 24, W = PAD + 840 + PAD + 280 + PAD, H = PAD + 500 + PAD;
  const pv = L.make(W, H, [28, 28, 34, 255]);
  L.blit(pv, back, PAD, PAD);
  const rx = PAD + 840 + PAD; L.blit(pv, st, rx, PAD);
  L.blit(pv, ic, rx, PAD + 158 + PAD);
  // circle-masked icon (2px anti-aliased edge so the bubble shape reads)
  const cx = rx + 128 + PAD + 64, cy = PAD + 158 + PAD + 64;
  const icx = rx + 128 + PAD, icy = PAD + 158 + PAD;
  for (let y = 0; y < 128; y++) for (let x = 0; x < 128; x++) {
    const d = Math.hypot(x + 0.5 - 64, y + 0.5 - 64), a = Math.max(0, Math.min(1, 64 - d));
    if (!a) continue; const s = (y * 128 + x) * 4, t = ((icy + y) * W + icx + x) * 4;
    for (let k = 0; k < 3; k++) pv.rgba[t + k] = Math.round(ic.rgba[s + k] * a + pv.rgba[t + k] * (1 - a));
  }
  // the same circle icon at half size, roughly how small it can appear on the home screen
  const small = L.make(64, 64);
  for (let y = 0; y < 64; y++) for (let x = 0; x < 64; x++) { let r = 0, g = 0, b = 0; for (let j = 0; j < 2; j++) for (let i = 0; i < 2; i++) { const s = ((y * 2 + j) * 128 + x * 2 + i) * 4; r += ic.rgba[s]; g += ic.rgba[s + 1]; b += ic.rgba[s + 2]; } const t = (y * 64 + x) * 4; small.rgba[t] = r / 4; small.rgba[t + 1] = g / 4; small.rgba[t + 2] = b / 4; small.rgba[t + 3] = 255; }
  const sx = rx, sy = PAD + 158 + PAD + 128 + PAD;
  for (let y = 0; y < 64; y++) for (let x = 0; x < 64; x++) { const d = Math.hypot(x + 0.5 - 32, y + 0.5 - 32), a = Math.max(0, Math.min(1, 32 - d)); if (!a) continue; const s = (y * 64 + x) * 4, t = ((sy + y) * W + sx + x) * 4; for (let k = 0; k < 3; k++) pv.rgba[t + k] = Math.round(small.rgba[s + k] * a + pv.rgba[t + k] * (1 - a)); }
  fs.writeFileSync(path.join(OUT, 'preview.png'), L.pngRGBA(pv));
  console.log('preview.png', `${W}x${H}`);
}
