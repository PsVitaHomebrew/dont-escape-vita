// Tiny static file server for the preview. Serves only files under the given root.
// Usage: node serve.js <root> <port>
'use strict';
const http = require('http'), fs = require('fs'), path = require('path');
const root = path.resolve(process.argv[2]); const port = +process.argv[3] || 51888;
const types = { '.html': 'text/html; charset=utf-8', '.json': 'application/json', '.png': 'image/png', '.js': 'text/javascript', '.txt': 'text/plain; charset=utf-8' };
http.createServer((req, res) => {
  const u = decodeURIComponent(new URL(req.url, 'http://x').pathname);
  const p = path.resolve(root, '.' + u);
  if (!p.startsWith(root)) { res.writeHead(403); return res.end(); }
  fs.readFile(p, (e, d) => {
    if (e) { res.writeHead(404); return res.end('not found'); }
    res.writeHead(200, { 'Content-Type': types[path.extname(p).toLowerCase()] || 'application/octet-stream', 'Cache-Control': 'no-store' });
    res.end(d);
  });
}).listen(port, '127.0.0.1', () => console.log('serving', root, 'on', port));
