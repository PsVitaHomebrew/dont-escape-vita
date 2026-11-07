// Compact zlib/deflate decoder (stored, fixed and dynamic Huffman blocks). Returns false on corrupt data.
#pragma once
#include <cstdint>
#include <cstring>
#include <vector>

namespace inflate_ns {
struct Bits {
  const uint8_t* p; size_t n, pos = 0; uint32_t buf = 0; int cnt = 0; bool bad = false;
  int bit() { if (!cnt) { if (pos >= n) { bad = true; return 0; } buf = p[pos++]; cnt = 8; } int b = buf & 1; buf >>= 1; cnt--; return b; }
  uint32_t bits(int k) { uint32_t v = 0; for (int i = 0; i < k; i++) v |= (uint32_t)bit() << i; return v; }
};
struct Huff { uint16_t count[16]; uint16_t sym[320]; };
inline void build(Huff& h, const uint8_t* len, int n) {
  uint16_t offs[16]; memset(h.count, 0, sizeof h.count);
  for (int i = 0; i < n; i++) h.count[len[i]]++;
  h.count[0] = 0; offs[1] = 0;
  for (int i = 1; i < 15; i++) offs[i + 1] = offs[i] + h.count[i];
  for (int i = 0; i < n; i++) if (len[i]) h.sym[offs[len[i]]++] = (uint16_t)i;
}
inline int decode(Bits& b, const Huff& h) {
  int code = 0, first = 0, index = 0;
  for (int len = 1; len < 16; len++) {
    code |= b.bit(); int count = h.count[len];
    if (code - count < first) return h.sym[index + (code - first)];
    index += count; first += count; first <<= 1; code <<= 1;
    if (b.bad) return -1;
  }
  return -1;
}
inline bool codes(Bits& b, std::vector<uint8_t>& out, const Huff& lit, const Huff& dist) {
  static const uint16_t lbase[29] = { 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258 };
  static const uint8_t lext[29] = { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0 };
  static const uint16_t dbase[30] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577 };
  static const uint8_t dext[30] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };
  for (;;) {
    int s = decode(b, lit); if (s < 0 || b.bad) return false;
    if (s < 256) out.push_back((uint8_t)s);
    else if (s == 256) return true;
    else {
      s -= 257; if (s >= 29) return false;
      int len = lbase[s] + (int)b.bits(lext[s]);
      int d = decode(b, dist); if (d < 0 || d >= 30) return false;
      size_t dd = dbase[d] + b.bits(dext[d]); if (dd > out.size()) return false;
      size_t from = out.size() - dd; for (int i = 0; i < len; i++) out.push_back(out[from + i]);
    }
  }
}
// zlib stream (2-byte header) -> out
inline bool zlibInflate(const uint8_t* src, size_t n, std::vector<uint8_t>& out, size_t expect = 0) {
  if (n < 2) return false;
  Bits b; b.p = src + 2; b.n = n - 2; out.clear(); if (expect) out.reserve(expect);
  Huff lit, dist; int last;
  do {
    last = b.bit(); int type = (int)b.bits(2);
    if (type == 0) {
      b.cnt = 0; if (b.pos + 4 > b.n) return false;
      unsigned len = b.p[b.pos] | (b.p[b.pos + 1] << 8); b.pos += 4;
      if (b.pos + len > b.n) return false;
      out.insert(out.end(), b.p + b.pos, b.p + b.pos + len); b.pos += len;
    } else if (type == 1) {
      uint8_t l[288]; int i = 0; for (; i < 144; i++) l[i] = 8; for (; i < 256; i++) l[i] = 9; for (; i < 280; i++) l[i] = 7; for (; i < 288; i++) l[i] = 8;
      build(lit, l, 288); uint8_t d[30]; for (i = 0; i < 30; i++) d[i] = 5; build(dist, d, 30);
      if (!codes(b, out, lit, dist)) return false;
    } else if (type == 2) {
      static const uint8_t ord[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
      int nlen = (int)b.bits(5) + 257, ndist = (int)b.bits(5) + 1, ncode = (int)b.bits(4) + 4;
      uint8_t lengths[320] = {}; for (int i = 0; i < ncode; i++) lengths[ord[i]] = (uint8_t)b.bits(3);
      Huff lc; build(lc, lengths, 19);
      int idx = 0; uint8_t all[320] = {};
      while (idx < nlen + ndist) {
        int s = decode(b, lc); if (s < 0) return false;
        if (s < 16) all[idx++] = (uint8_t)s;
        else {
          int rep = 0; uint8_t v = 0;
          if (s == 16) { if (!idx) return false; v = all[idx - 1]; rep = 3 + (int)b.bits(2); }
          else if (s == 17) rep = 3 + (int)b.bits(3); else rep = 11 + (int)b.bits(7);
          if (idx + rep > nlen + ndist) return false;
          while (rep--) all[idx++] = v;
        }
      }
      build(lit, all, nlen); build(dist, all + nlen, ndist);
      if (!codes(b, out, lit, dist)) return false;
    } else return false;
    if (b.bad) return false;
  } while (!last);
  return true;
}
} // namespace inflate_ns
