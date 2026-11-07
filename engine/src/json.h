// Small JSON DOM parser for the converter's output.
#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

struct JVal {
  enum T : uint8_t { Null, Bool, Num, Str, Arr, Obj } t = Null;
  double n = 0; bool b = false;
  std::string s;                                   // also object keys storage
  std::vector<JVal> a;                             // array items, or object values
  std::vector<std::string> k;                      // object keys (parallel to a)
  static const JVal& none() { static JVal z; return z; }
  bool isNull() const { return t == Null; }
  const JVal& operator[](size_t i) const { return (t == Arr && i < a.size()) ? a[i] : none(); }
  const JVal& operator[](int i) const { return (t == Arr && i >= 0 && (size_t)i < a.size()) ? a[i] : none(); }
  const JVal& operator[](const char* key) const {
    if (t != Obj) return none();
    for (size_t i = 0; i < k.size(); i++) if (k[i] == key) return a[i];
    return none();
  }
  bool has(const char* key) const { if (t != Obj) return false; for (auto& x : k) if (x == key) return true; return false; }
  size_t size() const { return a.size(); }
  double num(double d = 0) const { return t == Num ? n : t == Bool ? (b ? 1 : 0) : t == Str ? atof(s.c_str()) : d; }
  // via long long so 32-bit masks above INT_MAX (e.g. 4294967295) wrap to negative ints instead of overflowing
  int i(int d = 0) const { return t == Num ? (int)(uint32_t)(long long)n : t == Bool ? (b ? 1 : 0) : t == Str ? (int)(uint32_t)atoll(s.c_str()) : d; }
  float f(float d = 0) const { return (float)num(d); }
  const std::string& str() const { static std::string e; return t == Str ? s : e; }
};

class JParser {
  const char* p; const char* e;
  void ws() { while (p < e && (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')) p++; }
  void parseStr(std::string& out) {
    p++; // opening quote
    while (p < e && *p != '"') {
      if (*p == '\\') {
        p++;
        switch (*p) {
          case 'n': out += '\n'; break; case 't': out += '\t'; break; case 'r': out += '\r'; break;
          case 'b': out += '\b'; break; case 'f': out += '\f'; break;
          case 'u': {
            unsigned cp = strtoul(std::string(p + 1, 4).c_str(), nullptr, 16); p += 4;
            if (cp >= 0xD800 && cp < 0xDC00 && p[1] == '\\' && p[2] == 'u') { unsigned lo = strtoul(std::string(p + 3, 4).c_str(), nullptr, 16); cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00); p += 6; }
            if (cp < 0x80) out += (char)cp;
            else if (cp < 0x800) { out += (char)(0xC0 | (cp >> 6)); out += (char)(0x80 | (cp & 0x3f)); }
            else if (cp < 0x10000) { out += (char)(0xE0 | (cp >> 12)); out += (char)(0x80 | ((cp >> 6) & 0x3f)); out += (char)(0x80 | (cp & 0x3f)); }
            else { out += (char)(0xF0 | (cp >> 18)); out += (char)(0x80 | ((cp >> 12) & 0x3f)); out += (char)(0x80 | ((cp >> 6) & 0x3f)); out += (char)(0x80 | (cp & 0x3f)); }
            break;
          }
          default: out += *p;
        }
        p++;
      } else out += *p++;
    }
    p++;
  }
  void val(JVal& v) {
    ws();
    if (p >= e) return;
    char c = *p;
    if (c == '{') {
      v.t = JVal::Obj; p++;
      for (;;) {
        ws(); if (*p == '}') { p++; return; }
        v.k.emplace_back(); parseStr(v.k.back()); ws(); p++; // ':'
        v.a.emplace_back(); val(v.a.back()); ws();
        if (*p == ',') p++;
      }
    } else if (c == '[') {
      v.t = JVal::Arr; p++;
      for (;;) {
        ws(); if (*p == ']') { p++; return; }
        v.a.emplace_back(); val(v.a.back()); ws();
        if (*p == ',') p++;
      }
    } else if (c == '"') { v.t = JVal::Str; parseStr(v.s); }
    else if (c == 't') { v.t = JVal::Bool; v.b = true; p += 4; }
    else if (c == 'f') { v.t = JVal::Bool; v.b = false; p += 5; }
    else if (c == 'n') { v.t = JVal::Null; p += 4; }
    else { v.t = JVal::Num; char* end; v.n = strtod(p, &end); p = end; }
  }
public:
  static bool parse(const char* text, size_t len, JVal& out) { JParser j; j.p = text; j.e = text + len; j.val(out); return true; }
};
