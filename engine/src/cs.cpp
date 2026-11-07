#include "cs.h"
#include <cstdio>
#include <string>
#ifdef VITA
#include <psp2/kernel/threadmgr.h>
#endif
#include <cstdarg>
#include <ctime>

namespace cs {

void throwNull() { throw NullReferenceException(); }
const String String::Empty = String(std::u16string());

static void utf8to16(const char* s, size_t n, std::u16string& out) {
  out.clear(); out.reserve(n);
  for (size_t i = 0; i < n;) {
    unsigned c = (unsigned char)s[i];
    unsigned cp; int extra;
    if (c < 0x80) { cp = c; extra = 0; }
    else if ((c >> 5) == 6) { cp = c & 0x1f; extra = 1; }
    else if ((c >> 4) == 14) { cp = c & 0x0f; extra = 2; }
    else if ((c >> 3) == 30) { cp = c & 0x07; extra = 3; }
    else { out.push_back(0xFFFD); i++; continue; }
    if (i + extra >= n + (extra ? 0 : 1) && extra) { out.push_back(0xFFFD); break; }
    for (int k = 1; k <= extra; k++) cp = (cp << 6) | ((unsigned char)s[i + k] & 0x3f);
    i += 1 + extra;
    if (cp >= 0x10000) { cp -= 0x10000; out.push_back((char16_t)(0xD800 + (cp >> 10))); out.push_back((char16_t)(0xDC00 + (cp & 0x3ff))); }
    else out.push_back((char16_t)cp);
  }
}

String::String(const char* s) { if (s) { std::u16string u; utf8to16(s, strlen(s), u); p = std::make_shared<const std::u16string>(std::move(u)); } }
String String::FromUtf8(const char* s, size_t n) { std::u16string u; utf8to16(s, n, u); return String(std::move(u)); }

std::string String::utf8() const {
  std::string o; if (!p) return o;
  const auto& s = *p;
  for (size_t i = 0; i < s.size(); i++) {
    unsigned cp = s[i];
    if (cp >= 0xD800 && cp < 0xDC00 && i + 1 < s.size()) { cp = 0x10000 + ((cp - 0xD800) << 10) + (s[i + 1] - 0xDC00); i++; }
    if (cp < 0x80) o += (char)cp;
    else if (cp < 0x800) { o += (char)(0xC0 | (cp >> 6)); o += (char)(0x80 | (cp & 0x3f)); }
    else if (cp < 0x10000) { o += (char)(0xE0 | (cp >> 12)); o += (char)(0x80 | ((cp >> 6) & 0x3f)); o += (char)(0x80 | (cp & 0x3f)); }
    else { o += (char)(0xF0 | (cp >> 18)); o += (char)(0x80 | ((cp >> 12) & 0x3f)); o += (char)(0x80 | ((cp >> 6) & 0x3f)); o += (char)(0x80 | (cp & 0x3f)); }
  }
  return o;
}

String operator+(const String& a, const String& b) { std::u16string r = a.u(); r += b.u(); return String(std::move(r)); }

int String::IndexOf(const String& s, int start) const { if (!p) throwNull(); if (start < 0 || start > (int)p->size()) throw ArgumentOutOfRangeException(); auto r = p->find(s.u(), start); return r == std::u16string::npos ? -1 : (int)r; }
int String::IndexOf(char16_t c, int start) const { if (!p) throwNull(); if (start < 0 || start > (int)p->size()) throw ArgumentOutOfRangeException(); auto r = p->find(c, start); return r == std::u16string::npos ? -1 : (int)r; }
int String::LastIndexOf(const String& s) const { if (!p) throwNull(); auto r = p->rfind(s.u()); return r == std::u16string::npos ? -1 : (int)r; }
int String::LastIndexOf(char16_t c) const { if (!p) throwNull(); auto r = p->rfind(c); return r == std::u16string::npos ? -1 : (int)r; }
bool String::StartsWith(const String& s) const { if (!p) throwNull(); return p->compare(0, s.u().size(), s.u()) == 0 && p->size() >= s.u().size(); }
bool String::EndsWith(const String& s) const { if (!p) throwNull(); const auto& a = *p; const auto& b = s.u(); return a.size() >= b.size() && a.compare(a.size() - b.size(), b.size(), b) == 0; }
String String::Substring(int start) const { if (!p) throwNull(); if (start < 0 || start > (int)p->size()) throw ArgumentOutOfRangeException(); return String(p->substr(start)); }
String String::Substring(int start, int len) const { if (!p) throwNull(); if (start < 0 || len < 0 || start + len > (int)p->size()) throw ArgumentOutOfRangeException(); return String(p->substr(start, len)); }
String String::Replace(const String& a, const String& b) const {
  if (!p) throwNull(); const auto& f = a.u(); if (f.empty()) throw Exception("ArgumentException");
  std::u16string r; size_t i = 0;
  for (;;) { size_t k = p->find(f, i); if (k == std::u16string::npos) { r.append(*p, i, std::u16string::npos); break; } r.append(*p, i, k - i); r += b.u(); i = k + f.size(); }
  return String(std::move(r));
}
String String::Replace(char16_t a, char16_t b) const { if (!p) throwNull(); std::u16string r = *p; for (auto& c : r) if (c == a) c = b; return String(std::move(r)); }
String String::Insert(int at, const String& s) const { if (!p) throwNull(); if (at < 0 || at > (int)p->size()) throw ArgumentOutOfRangeException(); std::u16string r = *p; r.insert(at, s.u()); return String(std::move(r)); }
String String::Remove(int start) const { if (!p) throwNull(); if (start < 0 || start > (int)p->size()) throw ArgumentOutOfRangeException(); return String(p->substr(0, start)); }
String String::Remove(int start, int count) const { if (!p) throwNull(); if (start < 0 || count < 0 || start + count > (int)p->size()) throw ArgumentOutOfRangeException(); std::u16string r = *p; r.erase(start, count); return String(std::move(r)); }

char16_t char_ToLower(char16_t c) {
  if (c >= u'A' && c <= u'Z') return c + 32;
  if (c >= 0xC0 && c <= 0xDE && c != 0xD7) return c + 32;
  if (c >= 0x100 && c <= 0x137 && !(c & 1)) return c + 1;
  if (c >= 0x139 && c <= 0x148 && (c & 1)) return c + 1;
  if (c >= 0x14A && c <= 0x177 && !(c & 1)) return c + 1;
  if (c == 0x178) return 0xFF;
  if (c >= 0x179 && c <= 0x17E && (c & 1)) return c + 1;
  if (c >= 0x410 && c <= 0x42F) return c + 32;
  return c;
}
char16_t char_ToUpper(char16_t c) {
  if (c >= u'a' && c <= u'z') return c - 32;
  if (c >= 0xE0 && c <= 0xFE && c != 0xF7) return c - 32;
  if (c >= 0x101 && c <= 0x138 && (c & 1)) return c - 1;
  if (c >= 0x13A && c <= 0x149 && !(c & 1)) return c - 1;
  if (c >= 0x14B && c <= 0x178 && (c & 1)) return c - 1;
  if (c == 0xFF) return 0x178;
  if (c >= 0x17A && c <= 0x17F && !(c & 1)) return c - 1;
  if (c >= 0x430 && c <= 0x44F) return c - 32;
  return c;
}
String String::ToLower() const { if (!p) throwNull(); std::u16string r = *p; for (auto& c : r) c = char_ToLower(c); return String(std::move(r)); }
String String::ToUpper() const { if (!p) throwNull(); std::u16string r = *p; for (auto& c : r) c = char_ToUpper(c); return String(std::move(r)); }
String String::Trim() const { return TrimStart().TrimEnd(); }
String String::TrimEnd() const { if (!p) throwNull(); size_t e = p->size(); while (e > 0 && char_IsWhiteSpace((*p)[e - 1])) e--; return String(p->substr(0, e)); }
String String::TrimStart() const { if (!p) throwNull(); size_t b = 0; while (b < p->size() && char_IsWhiteSpace((*p)[b])) b++; return String(p->substr(b)); }
String String::PadLeft(int n, char16_t c) const { if (!p) throwNull(); std::u16string r = *p; while ((int)r.size() < n) r.insert(r.begin(), c); return String(std::move(r)); }
String String::PadRight(int n, char16_t c) const { if (!p) throwNull(); std::u16string r = *p; while ((int)r.size() < n) r.push_back(c); return String(std::move(r)); }
Array<String> String::Split(char16_t sep) const { return Split(Array<char16_t>::Of({ sep })); }
Array<String> String::Split(const Array<char16_t>& seps) const {
  if (!p) throwNull(); Array<String> out = Array<String>::New(0); std::u16string cur;
  Array<char16_t> sp = seps;
  auto isSep = [&](char16_t c) { if (sp.isNull() || sp.Length() == 0) return char_IsWhiteSpace(c); for (int i = 0; i < sp.Length(); i++) if (sp[i] == c) return true; return false; };
  for (char16_t c : *p) { if (isSep(c)) { out.vec().push_back(String(cur)); cur.clear(); } else cur.push_back(c); }
  out.vec().push_back(String(cur));
  return out;
}
Array<char16_t> String::ToCharArray() const { if (!p) throwNull(); Array<char16_t> a = Array<char16_t>::New((int)p->size()); for (size_t i = 0; i < p->size(); i++) a[(int)i] = (*p)[i]; return a; }
bool String::Equals(const String& o) const { if (!p) throwNull(); return *this == o; }
int String::CompareTo(const String& o) const { if (!p) throwNull(); if (!o.p) return 1; int c = p->compare(*o.p); return c < 0 ? -1 : c > 0 ? 1 : 0; }
int String::GetHashCode() const { int h = 5381; for (char16_t c : u()) h = h * 33 + c; return h; }
String String::FromChars(const Array<char16_t>& chars) { Array<char16_t> c = chars; std::u16string r; for (int i = 0; i < c.Length(); i++) r.push_back(c[i]); return String(std::move(r)); }
String String::Join(const String& sep, const Array<String>& parts) { std::u16string r; Array<String> pp = parts; for (int i = 0; i < pp.Length(); i++) { if (i) r += sep.u(); r += pp[i].u(); } return String(std::move(r)); }

String str(int v) { char b[16]; snprintf(b, sizeof b, "%d", v); return String(b); }
String str(unsigned v) { char b[16]; snprintf(b, sizeof b, "%u", v); return String(b); }
String str(long long v) { char b[24]; snprintf(b, sizeof b, "%lld", v); return String(b); }
static String fmtG(double v, int prec) {
  if (std::isnan(v)) return String("NaN");
  if (std::isinf(v)) return String(v > 0 ? "Infinity" : "-Infinity");
  if (v == 0) return String("0");
  char b[40]; snprintf(b, sizeof b, "%.*G", prec, v);
  // .NET writes exponents as E+07 / E-05 (at least two digits), C does the same; strip "+0" padding beyond 2 digits
  std::string s = b; size_t e = s.find('E');
  if (e != std::string::npos) {
    std::string mant = s.substr(0, e), ex = s.substr(e + 1); char sign = ex[0]; std::string digits = ex.substr(1);
    while (digits.size() > 2 && digits[0] == '0') digits.erase(0, 1);
    s = mant + "E" + sign + digits;
  }
  return String(s.c_str());
}
String str(float v) { return fmtG(v, 7); }
String str(double v) { return fmtG(v, 15); }
String str(bool v) { return String(v ? "True" : "False"); }
String str(char16_t v) { return String(std::u16string(1, v)); }

int int_Parse(const String& s) {
  std::string t = s.Trim().utf8(); if (t.empty()) throw FormatException();
  char* end; long v = strtol(t.c_str(), &end, 10); if (*end) throw FormatException(); return (int)v;
}
bool int_TryParse(const String& s, int& out) { try { out = int_Parse(s); return true; } catch (...) { out = 0; return false; } }
float float_Parse(const String& s) {
  std::string t = s.Trim().utf8(); for (auto& c : t) if (c == ',') c = '.';
  if (t.empty()) throw FormatException(); char* end; float v = strtof(t.c_str(), &end); if (*end) throw FormatException(); return v;
}
bool bool_Parse(const String& s) { std::string t = s.Trim().ToLower().utf8(); if (t == "true") return true; if (t == "false") return false; throw FormatException(); }

double Math_Round(double v) {
  double f = std::floor(v), d = v - f;
  if (d > 0.5) return f + 1; if (d < 0.5) return f;
  return std::fmod(f, 2.0) == 0 ? f : f + 1;
}

DateTime DateTime::Now() { time_t t = time(nullptr); struct tm lt = *localtime(&t); DateTime d; d.year = lt.tm_year + 1900; d.month = lt.tm_mon + 1; d.day = lt.tm_mday; d.hour = lt.tm_hour; d.minute = lt.tm_min; d.second = lt.tm_sec; return d; }
long long DateTime::get_Ticks() const { long long days = (long long)(year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400; static const int cum[12] = { 0,31,59,90,120,151,181,212,243,273,304,334 }; days += cum[(month > 0 ? month : 1) - 1] + day - 1; if (month > 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) days++; return ((days * 24 + hour) * 60 + minute) * 600000000LL + second * 10000000LL; }
String DateTime::ToShortDateString() const { char b[32]; snprintf(b, sizeof b, "%02d/%02d/%04d", month, day, year); return String(b); }
String DateTime::ToShortTimeString() const { char b[32]; int h = hour % 12; if (!h) h = 12; snprintf(b, sizeof b, "%d:%02d %s", h, minute, hour < 12 ? "AM" : "PM"); return String(b); }
String DateTime::ToString() const { return ToShortDateString() + String(" ") + ToShortTimeString(); }

static FILE* g_log = nullptr;
#ifdef VITA
// Vita: writing and flushing the log on the memory card took a few ms per line, and the game's scripts print a lot
// (6-8 lines per click), which made clicks stutter. Lines go into a memory buffer; a background thread writes them
// out every 200 ms (a crash can lose the last fifth of a second of log).
static SceKernelLwMutexWork g_bufLock, g_fileLock; static bool g_logThread = false; static std::string g_logBuf;
static void writePending() {
  std::string out;
  sceKernelLockLwMutex(&g_bufLock, 1, nullptr); out.swap(g_logBuf); sceKernelUnlockLwMutex(&g_bufLock, 1);
  if (out.empty()) return;
  sceKernelLockLwMutex(&g_fileLock, 1, nullptr);
  if (g_log) { fwrite(out.data(), 1, out.size(), g_log); fflush(g_log); }
  sceKernelUnlockLwMutex(&g_fileLock, 1);
}
static int logThread(SceSize, void*) { for (;;) { sceKernelDelayThread(200000); writePending(); } return 0; }
void logFlush() { if (g_logThread) writePending(); }
void setLogFile(const char* path) {
  if (!g_logThread) {
    sceKernelCreateLwMutex(&g_bufLock, "log_buf", 0, 0, nullptr); sceKernelCreateLwMutex(&g_fileLock, "log_file", 0, 0, nullptr);
    SceUID t = sceKernelCreateThread("log_writer", logThread, 0x10000120, 0x4000, 0, 0x40000 /* core 2 */, NULL);
    if (t >= 0 && sceKernelStartThread(t, 0, NULL) >= 0) g_logThread = true;
  }
  if (g_logThread) writePending();   // what was logged so far goes to the old file
  if (g_logThread) sceKernelLockLwMutex(&g_fileLock, 1, nullptr);
  if (g_log) fclose(g_log);
  g_log = fopen(path, "w");
  if (g_logThread) sceKernelUnlockLwMutex(&g_fileLock, 1);
}
void log(const char* fmt, ...) {
  char buf[2048]; va_list ap; va_start(ap, fmt); vsnprintf(buf, sizeof buf, fmt, ap); va_end(ap);
  if (!g_logThread) { if (g_log) { fputs(buf, g_log); fputc('\n', g_log); fflush(g_log); } return; }
  sceKernelLockLwMutex(&g_bufLock, 1, nullptr); g_logBuf += buf; g_logBuf += '\n'; sceKernelUnlockLwMutex(&g_bufLock, 1);
}
#else
void logFlush() { if (g_log) fflush(g_log); }
void setLogFile(const char* path) { if (g_log) fclose(g_log); g_log = fopen(path, "w"); }
void log(const char* fmt, ...) {
  char buf[2048]; va_list ap; va_start(ap, fmt); vsnprintf(buf, sizeof buf, fmt, ap); va_end(ap);
  fputs(buf, stdout); fputc('\n', stdout);
  if (g_log) { fputs(buf, g_log); fputc('\n', g_log); fflush(g_log); }
}
#endif
} // namespace cs
