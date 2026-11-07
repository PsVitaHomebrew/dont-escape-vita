// Writes <data>/checksums.txt: one line per data file, "crc32hex size relative/path".
// The Vita build checks the card's copy against it once (main_vita.cpp checkData) and logs damaged files.
// usage: node checksums.js <data folder>
const fs = require('fs'), path = require('path');
const root = process.argv[2] || 'data';
const table = new Uint32Array(256);
for (let n = 0; n < 256; n++) { let c = n; for (let k = 0; k < 8; k++) c = c & 1 ? 0xEDB88320 ^ (c >>> 1) : c >>> 1; table[n] = c >>> 0; }
const crc32 = buf => { let c = 0xFFFFFFFF; for (let i = 0; i < buf.length; i++) c = table[(c ^ buf[i]) & 0xFF] ^ (c >>> 8); return (c ^ 0xFFFFFFFF) >>> 0; };
const lines = [];
const walk = dir => {
  for (const e of fs.readdirSync(dir, { withFileTypes: true }).sort((a, b) => a.name < b.name ? -1 : 1)) {
    if (e.name.startsWith('.')) continue;   // skip Mac ._ files and other dot files
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p);
    else if (e.name !== 'checksums.txt') {
      const b = fs.readFileSync(p);
      lines.push(crc32(b).toString(16).padStart(8, '0') + ' ' + b.length + ' ' + path.relative(root, p).split(path.sep).join('/'));
    }
  }
};
walk(root);
fs.writeFileSync(path.join(root, 'checksums.txt'), lines.join('\n') + '\n');
console.log('checksums.txt:', lines.length, 'files');
