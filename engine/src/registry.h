// Script class registry (filled in by generated code) and typed reading of scene/prefab script fields.
#pragma once
#include "unity.h"
#include "json.h"

// Argument for animation events and Invoke: Unity passes string/float/int/object depending on the method.
struct EventArg { String s; float f = 0; int i = 0; P<Object> o; bool has = false; };

using MsgFn = void (*)(MonoBehaviour*);
struct ClassInfo {
  const char* name = "";
  const char* base = "";
  int execOrder = 0;
  MonoBehaviour* (*create)() = nullptr;
  // Unity messages: generated to point at the most-derived declaration (C# private methods are not virtual)
  MsgFn Awake = nullptr, Start = nullptr, Update = nullptr, LateUpdate = nullptr, OnEnable = nullptr, OnDisable = nullptr, OnDestroy = nullptr;
  MsgFn OnMouseDown = nullptr, OnMouseUp = nullptr, OnMouseEnter = nullptr, OnMouseExit = nullptr, OnMouseOver = nullptr;
  void (*OnLevelWasLoaded)(MonoBehaviour*, int) = nullptr;
  // Invoke("name") / animation events: returns false when the class has no such method
  bool (*invoke)(MonoBehaviour*, const char* name, const EventArg& arg) = nullptr;
  mutable const ClassInfo* _baseInfo = nullptr; mutable bool _baseDone = false;   // engine: resolved `base` (GetComponent fast path)
};
void registerClass(const ClassInfo* ci);
const ClassInfo* findClass(const char* name);

// Resolves {r:fileID} (same scene/prefab) and {a:assetIndex} references while a scene is being built.
struct RefResolver {
  virtual P<Object> local(long long fileID) = 0;
  virtual P<Object> asset(int globalIndex, long long fileID) = 0;
  virtual ~RefResolver() {}
};

class FieldReader {
public:
  const JVal* v; RefResolver* res;
  FieldReader(const JVal* v_, RefResolver* r) : v(v_), res(r) {}
  const JVal* field(const char* name) const { const JVal& x = (*v)[name]; return x.isNull() && !v->has(name) ? nullptr : &x; }

  // ---- scalars
  static void read(const JVal& j, int& out, RefResolver*) { out = j.i(); }
  static void read(const JVal& j, float& out, RefResolver*) { out = j.f(); }
  static void read(const JVal& j, double& out, RefResolver*) { out = j.num(); }
  static void read(const JVal& j, bool& out, RefResolver*) { out = j.i() != 0; }
  static void read(const JVal& j, long long& out, RefResolver*) { out = (long long)j.num(); }
  static void read(const JVal& j, uint8_t& out, RefResolver*) { out = (uint8_t)j.i(); }
  static void read(const JVal& j, int8_t& out, RefResolver*) { out = (int8_t)j.i(); }
  static void read(const JVal& j, short& out, RefResolver*) { out = (short)j.i(); }
  static void read(const JVal& j, uint16_t& out, RefResolver*) { out = (uint16_t)j.i(); }
  static void read(const JVal& j, unsigned& out, RefResolver*) { out = (unsigned)j.i(); }
  static void read(const JVal& j, unsigned long long& out, RefResolver*) { out = (unsigned long long)j.num(); }
  static void read(const JVal& j, char16_t& out, RefResolver*) { out = (char16_t)j.i(); }
  static void read(const JVal& j, String& out, RefResolver*) { out = String(j.str().c_str()); }
  template <class E, std::enable_if_t<std::is_enum_v<E>, int> = 0>
  static void read(const JVal& j, E& out, RefResolver*) { out = (E)j.i(); }
  // ---- Unity value types
  static void read(const JVal& j, Vector2& o, RefResolver*) { o = { j["x"].f(), j["y"].f() }; }
  static void read(const JVal& j, Vector3& o, RefResolver*) { o = { j["x"].f(), j["y"].f(), j["z"].f() }; }
  static void read(const JVal& j, Vector4& o, RefResolver*) { o = { j["x"].f(), j["y"].f(), j["z"].f(), j["w"].f() }; }
  static void read(const JVal& j, Color& o, RefResolver*) { o = { j["r"].f(), j["g"].f(), j["b"].f(), j["a"].f() }; }
  static void read(const JVal& j, Rect& o, RefResolver*) { o = { j["x"].f(), j["y"].f(), j["width"].f(), j["height"].f() }; }
  static void read(const JVal& j, LayerMask& o, RefResolver*) { o.value = j["m_Bits"].i(); }
  static void read(const JVal& j, DateTime& d, RefResolver*) { if (j.t != JVal::Obj) return; d.year = j["y"].i(); d.month = j["mo"].i(); d.day = j["d"].i(); d.hour = j["h"].i(); d.minute = j["mi"].i(); d.second = j["s"].i(); }
  // ---- references and serializable classes
  template <class T> static void read(const JVal& j, P<T>& out, RefResolver* r) {
    if constexpr (std::is_base_of_v<Object, T>) {
      out = nullptr;
      if (j.t != JVal::Obj) return;
      P<Object> o;
      if (j.has("r")) o = r->local((long long)j["r"].num());
      else if (j.has("a")) o = r->asset(j["a"].i(), j.has("f") ? (long long)j["f"].num() : 0);
      out = o.template as<T>();
      // A component field pointing at a GameObject in Unity data never happens; GameObject field pointing at component does not either.
    } else {
      // [Serializable] plain class: Unity always creates an instance
      out = P<T>(new T());
      if (j.t == JVal::Obj) { FieldReader sub(&j, r); out->_load(sub); }
    }
  }
  // Unity's text format stores arrays of plain numbers/bools/enums as one little-endian hex string ("0100" ...)
  template <class T> static bool readHex(const JVal& j, std::vector<T>& out) {
    if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T>) {
      if (j.t != JVal::Str) return false;
      const std::string& h = j.str(); const size_t es = sizeof(T);
      if (h.size() % (es * 2)) return false;
      for (size_t i = 0; i + es * 2 <= h.size(); i += es * 2) {
        uint8_t b[8] = {};
        for (size_t k = 0; k < es; k++) b[k] = (uint8_t)strtol(h.substr(i + 2 * k, 2).c_str(), nullptr, 16);
        T v; memcpy(&v, b, es); out.push_back(v);
      }
      return true;
    } else { (void)j; (void)out; return false; }
  }
  template <class T> static void read(const JVal& j, List<T>& out, RefResolver* r) {
    out = List<T>::New();
    std::vector<T> hex; if (readHex(j, hex)) { for (size_t i = 0; i < hex.size(); i++) out.Add((T)hex[i]); return; }
    for (size_t i = 0; i < j.size(); i++) { T x{}; read(j[i], x, r); out.Add(x); }
  }
  template <class T> static void read(const JVal& j, Array<T>& out, RefResolver* r) {
    std::vector<T> hex; if (readHex(j, hex)) { out = Array<T>::New((int)hex.size()); for (size_t i = 0; i < hex.size(); i++) out[(int)i] = hex[i]; return; }
    out = Array<T>::New((int)j.size());
    for (size_t i = 0; i < j.size(); i++) { T x{}; read(j[i], x, r); out[(int)i] = x; }
  }
  // value-type structs from the game implement _load too
  template <class T, std::enable_if_t<std::is_class_v<T> && !std::is_base_of_v<Obj, T>, int> = 0>
  static auto read(const JVal& j, T& out, RefResolver* r) -> decltype(out._load(std::declval<FieldReader&>()), void()) { FieldReader sub(&j, r); out._load(sub); }

  // Used by generated _load(): only assigns when the field exists in the data.
  template <class T> void get(const char* name, T& out) { if (const JVal* j = field(name)) read(*j, out, res); }
};

// Writes [Serializable] game objects as JSON (the BinaryFormatter stand-in reads them back with FieldReader).
class JsonWriter {
public:
  std::string out; bool first = true;
  std::function<void(JsonWriter&, Obj*)> refWriter;   // set by Instantiate: writes {"r":id} for Unity objects
  void key(const char* k) { if (!first) out += ','; first = false; out += '"'; out += k; out += "\":"; }
  void str(const String& s) {
    if (s.isNull()) { out += "\"\""; return; }
    out += '"'; for (char c : s.utf8()) { if (c == '"' || c == '\\') { out += '\\'; out += c; } else if (c == '\n') out += "\\n"; else if (c == '\r') out += "\\r"; else if (c == '\t') out += "\\t"; else out += c; } out += '"';
  }
  void val(int v) { out += std::to_string(v); } void val(unsigned v) { out += std::to_string(v); }
  void val(long long v) { out += std::to_string(v); } void val(unsigned long long v) { out += std::to_string(v); }
  void val(short v) { out += std::to_string(v); } void val(uint16_t v) { out += std::to_string(v); }
  void val(int8_t v) { out += std::to_string(v); } void val(uint8_t v) { out += std::to_string(v); }
  void val(char16_t v) { out += std::to_string((int)v); }
  void val(bool v) { out += v ? "1" : "0"; }
  void val(float v) { char b[32]; snprintf(b, sizeof b, "%.9g", v); out += b; }
  void val(double v) { char b[40]; snprintf(b, sizeof b, "%.17g", v); out += b; }
  void val(const String& s) { str(s); }
  template <class E, std::enable_if_t<std::is_enum_v<E>, int> = 0> void val(E e) { out += std::to_string((int)e); }
  void val(const Vector2& v) { out += "{\"x\":"; val(v.x); out += ",\"y\":"; val(v.y); out += '}'; }
  void val(const Vector3& v) { out += "{\"x\":"; val(v.x); out += ",\"y\":"; val(v.y); out += ",\"z\":"; val(v.z); out += '}'; }
  void val(const Color& c) { out += "{\"r\":"; val(c.r); out += ",\"g\":"; val(c.g); out += ",\"b\":"; val(c.b); out += ",\"a\":"; val(c.a); out += '}'; }
  void val(const Vector4& v) { out += "{\"x\":"; val(v.x); out += ",\"y\":"; val(v.y); out += ",\"z\":"; val(v.z); out += ",\"w\":"; val(v.w); out += '}'; }
  void val(const Rect& r) { out += "{\"x\":"; val(r.x); out += ",\"y\":"; val(r.y); out += ",\"width\":"; val(r.width); out += ",\"height\":"; val(r.height); out += '}'; }
  void val(const LayerMask& m) { out += "{\"m_Bits\":"; val(m.value); out += '}'; }
  void val(const DateTime& d) { out += "{\"y\":" + std::to_string(d.year) + ",\"mo\":" + std::to_string(d.month) + ",\"d\":" + std::to_string(d.day) + ",\"h\":" + std::to_string(d.hour) + ",\"mi\":" + std::to_string(d.minute) + ",\"s\":" + std::to_string(d.second) + "}"; }
  template <class T> void val(const P<T>& p) {
    if constexpr (std::is_base_of_v<Object, T>) { if (refWriter && !p.isNull()) refWriter(*this, p.obj()); else out += "null"; }   // saves never hold Unity objects
    else { if (p.isNull()) { out += "null"; return; } out += '{'; bool f = first; first = true; p->_save(*this); first = f; out += '}'; }
  }
  template <class T> void val(const List<T>& l) { if (l.isNull()) { out += "null"; return; } out += '['; List<T> c = l; for (int i = 0; i < c.Count(); i++) { if (i) out += ','; val((T)c[i]); } out += ']'; }
  template <class T> void val(const Array<T>& a) { if (a.isNull()) { out += "null"; return; } out += '['; Array<T> c = a; for (int i = 0; i < c.Length(); i++) { if (i) out += ','; val((T)c[i]); } out += ']'; }
  template <class T, std::enable_if_t<std::is_class_v<T> && !std::is_base_of_v<Obj, T>, int> = 0>
  auto val(const T& s) -> decltype(const_cast<T&>(s)._save(*this), void()) { out += '{'; bool f = first; first = true; const_cast<T&>(s)._save(*this); first = f; out += '}'; }
  template <class T> void put(const char* name, const T& v) { key(name); val(v); }
};

// ---- System.IO file streams + BinaryFormatter stand-in (saves are JSON, not .NET binary)
enum class FileMode : int { CreateNew = 1, Create = 2, Open = 3, OpenOrCreate = 4, Truncate = 5, Append = 6 };
class FileStream : public Obj {
public:
  std::string path; FileMode mode; bool closed = false;
  FileStream(std::string p, FileMode m) : path(std::move(p)), mode(m) {}
  void Close() { closed = true; }
  void Dispose() { closed = true; }
};
class BinaryFormatter {
public:
  template <class T> void Serialize(const P<FileStream>& fs, const P<T>& obj) {
    JsonWriter w; w.out = "{"; obj->_save(w); w.out += "}";
    FILE* f = fopen(fs->path.c_str(), "wb"); if (!f) throw Exception("could not write " + fs->path);
    fwrite(w.out.data(), 1, w.out.size(), f); fclose(f);
  }
  template <class T> P<T> Deserialize(const P<FileStream>& fs) {
    FILE* f = fopen(fs->path.c_str(), "rb"); if (!f) throw Exception("could not read " + fs->path);
    std::string s; char buf[4096]; size_t n; while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n); fclose(f);
    JVal j; JParser::parse(s.data(), s.size(), j);
    if (j.t != JVal::Obj) throw Exception("SerializationException: " + fs->path);
    P<T> out(new T()); FieldReader r(&j, nullptr); out->_load(r); return out;
  }
};
