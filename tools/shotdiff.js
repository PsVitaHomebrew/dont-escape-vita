// Compares smoke-test screenshots with a saved baseline: node shotdiff.js <baselineDir> <newDir>
// Prints each scene whose picture changed (pixels with any channel off by more than 8) and the changed area.
const fs = require('fs'), path = require('path');
const { decodePng } = require('./convert/png.js');
const [base, cur] = [process.argv[2] || 'run/baseline', process.argv[3] || 'run/smoke'];
let changed = 0, total = 0;
const files = fs.readdirSync(base).filter(f => /^s\d+\.png$/.test(f)).sort((a, b) => parseInt(a.slice(1)) - parseInt(b.slice(1)));
for (const f of files) {
  const pb = path.join(base, f), pc = path.join(cur, f);
  if (!fs.existsSync(pc)) { console.log(f, 'missing in new run'); changed++; continue; }
  const a = decodePng(fs.readFileSync(pb)), b = decodePng(fs.readFileSync(pc));
  const da = a.data || a.pixels || a.rgba, db = b.data || b.pixels || b.rgba, W = a.width || a.w;
  let n = 0, x0 = 1e9, y0 = 1e9, x1 = -1, y1 = -1;
  for (let i = 0; i < da.length; i += 4) {
    if (Math.abs(da[i] - db[i]) > 8 || Math.abs(da[i + 1] - db[i + 1]) > 8 || Math.abs(da[i + 2] - db[i + 2]) > 8) {
      n++; const p = i / 4, x = p % W, y = (p / W) | 0; if (x < x0) x0 = x; if (x > x1) x1 = x; if (y < y0) y0 = y; if (y > y1) y1 = y;
    }
  }
  total++;
  if (n) { changed++; console.log(f, n, 'pixels changed, area', x0, y0, '-', x1, y1); }
}
console.log(`${changed} of ${total} scenes differ`);
