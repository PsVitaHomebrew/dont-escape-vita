// Minimal PS Vita psp2dmp reader: gunzip (tolerating a truncated .tmp), list ELF program headers and notes.
// usage: node core.js <dump> [--hex NOTE]
const fs = require('fs'), zlib = require('zlib');
const raw = fs.readFileSync(process.argv[2]);
let buf;
try { buf = zlib.gunzipSync(raw); } catch (e) {
  // truncated gzip: inflate what is there
  const chunks = []; const inf = zlib.createGunzip();
  try { buf = zlib.gunzipSync(raw, { finishFlush: zlib.constants.Z_SYNC_FLUSH }); } catch (e2) { console.error('gunzip failed', e2.message); process.exit(1); }
}
fs.writeFileSync(process.argv[2] + '.elf', buf);
const u16 = o => buf.readUInt16LE(o), u32 = o => buf.readUInt32LE(o);
console.log('size', buf.length, 'magic', buf.slice(0, 4).toString('hex'), 'type', u16(16), 'machine', u16(18));
const phoff = u32(28), phentsize = u16(42), phnum = u16(44);
const notes = [];
for (let i = 0; i < phnum; i++) {
  const o = phoff + i * phentsize;
  const type = u32(o), off = u32(o + 4), vaddr = u32(o + 8), filesz = u32(o + 16), memsz = u32(o + 20), flags = u32(o + 24);
  if (type === 4) {
    // PT_NOTE: one or more notes
    let p = off; const end = Math.min(off + filesz, buf.length);
    while (p + 12 <= end) {
      const ns = u32(p), ds = u32(p + 4), nt = u32(p + 8);
      const name = buf.slice(p + 12, p + 12 + ns).toString('latin1').replace(/\0+$/, '');
      const dOff = p + 12 + ((ns + 3) & ~3);
      notes.push({ name, type: nt, off: dOff, size: ds });
      p = dOff + ((ds + 3) & ~3);
    }
  } else if (i < 400) console.log(`seg ${i} type ${type} off 0x${off.toString(16)} vaddr 0x${vaddr.toString(16)} filesz 0x${filesz.toString(16)} memsz 0x${memsz.toString(16)} flags ${flags}`);
}
for (const n of notes) console.log(`note "${n.name}" type ${n.type} off 0x${n.off.toString(16)} size ${n.size}`);
const hexName = process.argv.indexOf('--hex') > 0 ? process.argv[process.argv.indexOf('--hex') + 1] : null;
if (hexName) for (const n of notes) if (n.name === hexName) {
  const b = buf.slice(n.off, n.off + Math.min(n.size, 4096));
  for (let i = 0; i < b.length; i += 16) console.log(i.toString(16).padStart(5, '0'), b.slice(i, i + 16).toString('hex').match(/../g).join(' '), b.slice(i, i + 16).toString('latin1').replace(/[^\x20-\x7e]/g, '.'));
}
