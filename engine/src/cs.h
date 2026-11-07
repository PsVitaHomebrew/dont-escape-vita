// C#-like runtime pieces used by the translated game code.
// Rules: reference types are P<T> (checked, ref-counted), strings are String (UTF-16, nullable),
// List<T>/Array<T> are shared handles like in C#. Null access throws NullReferenceException,
// which the engine catches per script call, the same way Unity logs and carries on.
#pragma once
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <stdexcept>

namespace cs {

// ------------------------------------------------------------------ exceptions
std::string captureStack();   // PC builds: " at Func (file:line) <- ..."; empty on the Vita
struct Exception : std::exception {
  std::string msg;
  explicit Exception(std::string m) : msg(std::move(m)) {}
  const char* what() const noexcept override { return msg.c_str(); }
};
struct NullReferenceException : Exception { NullReferenceException() : Exception("NullReferenceException" + captureStack()) {} };
struct IndexOutOfRangeException : Exception { IndexOutOfRangeException() : Exception("IndexOutOfRangeException" + captureStack()) {} };
struct ArgumentOutOfRangeException : Exception { ArgumentOutOfRangeException() : Exception("ArgumentOutOfRangeException" + captureStack()) {} };
struct FormatException : Exception { FormatException() : Exception("FormatException") {} };
struct InvalidCastException : Exception { InvalidCastException() : Exception("InvalidCastException") {} };
[[noreturn]] void throwNull();

// ------------------------------------------------------------------ ref-counted objects
struct Obj {
  int _rc = 0;
  Obj() {}
  Obj(const Obj&) {}                       // a copy is a new object: no references yet
  Obj& operator=(const Obj&) { return *this; }
  virtual ~Obj() {}
  // UnityEngine.Object overrides this: a destroyed object compares equal to null.
  virtual bool _isNullish() const { return false; }
};

// Holds an Obj* so that P<T> members work with only a forward declaration of T.
template <class T> class P {
  Obj* o = nullptr;
  template <class U> friend class P;
  void inc() { if (o) ++o->_rc; }
  void dec() { if (o && --o->_rc == 0) delete o; }
public:
  P() {}
  P(std::nullptr_t) {}
  P(T* x) : o(x ? static_cast<Obj*>(x) : nullptr) { inc(); }
  P(const P& x) : o(x.o) { inc(); }
  P(P&& x) noexcept : o(x.o) { x.o = nullptr; }
  template <class U, class = std::enable_if_t<std::is_convertible_v<U*, T*>>> P(const P<U>& x) : o(x.o) { inc(); }
  ~P() { dec(); }
  P& operator=(const P& x) { if (x.o) ++x.o->_rc; dec(); o = x.o; return *this; }
  P& operator=(P&& x) noexcept { if (this != &x) { dec(); o = x.o; x.o = nullptr; } return *this; }
  P& operator=(std::nullptr_t) { dec(); o = nullptr; return *this; }
  T* get() const { return static_cast<T*>(o); }   // raw, unchecked
  T* operator->() const { if (!o) throwNull(); return get(); }
  T& operator*() const { if (!o) throwNull(); return *get(); }
  Obj* obj() const { return o; }
  bool isNull() const { return !o || o->_isNullish(); } // Unity-style null
  explicit operator bool() const { return !isNull(); }
  template <class U> P<U> as() const { return P<U>(dynamic_cast<U*>(o)); }   // C# "as"
  template <class U> P<U> cast() const { if (!o) return nullptr; U* u = dynamic_cast<U*>(o); if (!u) throw InvalidCastException(); return P<U>(u); } // C# (U)x
  template <class U> bool is() const { return o && dynamic_cast<U*>(o) != nullptr; } // C# "is"
};
// C# "x == null" / "x != null" with Unity semantics for UnityEngine.Object
template <class T> bool operator==(const P<T>& a, std::nullptr_t) { return a.isNull(); }
template <class T> bool operator!=(const P<T>& a, std::nullptr_t) { return !a.isNull(); }
template <class T> bool operator==(std::nullptr_t, const P<T>& a) { return a.isNull(); }
template <class T> bool operator!=(std::nullptr_t, const P<T>& a) { return !a.isNull(); }
// Reference equality (Unity: two destroyed objects are both "null" and therefore equal)
template <class T, class U> bool operator==(const P<T>& a, const P<U>& b) {
  bool an = a.isNull(), bn = b.isNull(); if (an || bn) return an == bn;
  return a.obj() == b.obj();
}
template <class T, class U> bool operator!=(const P<T>& a, const P<U>& b) { return !(a == b); }
template <class T, class... A> P<T> New(A&&... a) { return P<T>(new T(std::forward<A>(a)...)); }

// ------------------------------------------------------------------ String (UTF-16 like .NET)
class String;
template <class T> class Array;
class String {
  std::shared_ptr<const std::u16string> p;
public:
  String() {}
  String(std::nullptr_t) {}
  String(const char* utf8);
  String(const char16_t* s) : p(s ? std::make_shared<const std::u16string>(s) : nullptr) {}
  String(std::u16string s) : p(std::make_shared<const std::u16string>(std::move(s))) {}
  static const String Empty;
  static String FromUtf8(const char* s, size_t n);
  bool isNull() const { return !p; }
  const std::u16string& u() const { static const std::u16string e; return p ? *p : e; }
  std::string utf8() const;
  int Length() const { if (!p) throwNull(); return (int)p->size(); }
  char16_t operator[](int i) const { if (!p) throwNull(); if (i < 0 || i >= (int)p->size()) throw IndexOutOfRangeException(); return (*p)[i]; }
  int IndexOf(const String& s, int start = 0) const;
  int IndexOf(char16_t c, int start = 0) const;
  int LastIndexOf(const String& s) const;
  int LastIndexOf(char16_t c) const;
  bool Contains(const String& s) const { return IndexOf(s) >= 0; }
  bool StartsWith(const String& s) const;
  bool EndsWith(const String& s) const;
  String Substring(int start) const;
  String Substring(int start, int len) const;
  String Replace(const String& a, const String& b) const;
  String Replace(char16_t a, char16_t b) const;
  String Insert(int at, const String& s) const;
  String Remove(int start) const;
  String Remove(int start, int count) const;
  String ToLower() const;
  String ToUpper() const;
  String Trim() const;
  String TrimEnd() const;
  String TrimStart() const;
  String PadLeft(int n, char16_t c = u' ') const;
  String PadRight(int n, char16_t c = u' ') const;
  Array<String> Split(char16_t sep) const;
  Array<String> Split(const Array<char16_t>& seps) const;
  Array<char16_t> ToCharArray() const;
  bool Equals(const String& o) const;
  int CompareTo(const String& o) const;
  String ToString() const { return *this; }
  int GetHashCode() const;
  static bool IsNullOrEmpty(const String& s) { return !s.p || s.p->empty(); }
  static String Concat(const String& a, const String& b) { return a + b; }
  static String Concat(const String& a, const String& b, const String& c) { return a + b + c; }
  static String Concat(const String& a, const String& b, const String& c, const String& d) { return a + b + c + d; }
  static String Join(const String& sep, const Array<String>& parts);
  static String FromChars(const Array<char16_t>& chars);   // C#: new string(chars)
  friend String operator+(const String& a, const String& b);
  String& operator+=(const String& b) { *this = *this + b; return *this; }
  String& operator+=(char16_t c) { std::u16string r = u(); r.push_back(c); *this = String(std::move(r)); return *this; }
  String& operator+=(const char* b) { *this = *this + String(b); return *this; }
  friend bool operator==(const String& a, const String& b) { if (!a.p || !b.p) return !a.p && !b.p; return *a.p == *b.p; }
  friend bool operator!=(const String& a, const String& b) { return !(a == b); }
  friend bool operator==(const String& a, std::nullptr_t) { return !a.p; }
  friend bool operator!=(const String& a, std::nullptr_t) { return (bool)a.p; }
  friend bool operator<(const String& a, const String& b) { return a.u() < b.u(); }
};
inline String S(const char* s) { return String(s); }   // builds a new String every call (S() below is the cached form)
// S("text") turns a string literal into a String. Each call site builds its String once and shares it after that
// (Strings are immutable), saving a heap allocation and a UTF-8 decode every time the line runs: a big cost on
// the Vita, where scripts run S() thousands of times a frame. Only ever pass a string literal.
#define S(lit) ([]() -> const ::cs::String& { static const ::cs::String* s_lit_ = new ::cs::String(lit); return *s_lit_; }())

// C#-style formatting of values
String str(int v);
String str(unsigned v);
String str(long long v);
String str(float v);     // .NET Single "G": 7 significant digits
String str(double v);    // .NET Double "G": 15 significant digits
String str(bool v);      // "True"/"False"
String str(char16_t v);
inline String str(const String& s) { return s; }
template <class T> String str(const P<T>& o) { return o.isNull() ? String::Empty : o->ToString(); }
// str(EnumValue) overloads (C# enum ToString gives the value name) are generated per enum.

inline String operator+(const String& a, int b) { return a + str(b); }
inline String operator+(int a, const String& b) { return str(a) + b; }
inline String operator+(const String& a, float b) { return a + str(b); }
inline String operator+(float a, const String& b) { return str(a) + b; }
inline String operator+(const String& a, double b) { return a + str(b); }
inline String operator+(const String& a, bool b) { return a + str(b); }
inline String operator+(const String& a, char16_t b) { return a + str(b); }
inline String operator+(char16_t a, const String& b) { return str(a) + b; }
inline String operator+(const String& a, const char* b) { return a + String(b); }
inline String operator+(const char* a, const String& b) { return String(a) + b; }
inline bool operator==(const String& a, const char* b) { return a == String(b); }
inline bool operator!=(const String& a, const char* b) { return !(a == String(b)); }

int int_Parse(const String& s);
float float_Parse(const String& s);
bool int_TryParse(const String& s, int& out);
bool bool_Parse(const String& s);
char16_t char_ToLower(char16_t c);
char16_t char_ToUpper(char16_t c);
inline bool char_IsDigit(char16_t c) { return c >= u'0' && c <= u'9'; }
inline bool char_IsWhiteSpace(char16_t c) { return c == u' ' || c == u'\t' || c == u'\n' || c == u'\r' || c == 0xA0; }

// ------------------------------------------------------------------ List<T> / Array<T>
template <class T> using Store = std::conditional_t<std::is_same_v<T, bool>, uint8_t, T>;

template <class T> class List {
  std::shared_ptr<std::vector<Store<T>>> v;
  template <class U> friend class Array;
  void chk() const { if (!v) throwNull(); }
public:
  using value_type = T;
  List() {}
  List(std::nullptr_t) {}
  static List New() { List l; l.v = std::make_shared<std::vector<Store<T>>>(); return l; }
  static List New(std::initializer_list<T> il) { List l = New(); for (auto& x : il) l.v->push_back(x); return l; }
  static List New(int capacity) { List l = New(); l.v->reserve(capacity > 0 ? capacity : 0); return l; }
  bool isNull() const { return !v; }
  int Count() const { chk(); return (int)v->size(); }
  Store<T>& operator[](int i) { chk(); if (i < 0 || i >= (int)v->size()) throw ArgumentOutOfRangeException(); return (*v)[i]; }
  const Store<T>& operator[](int i) const { chk(); if (i < 0 || i >= (int)v->size()) throw ArgumentOutOfRangeException(); return (*v)[i]; }
  void Add(const T& x) { chk(); v->push_back(x); }
  void AddRange(const List& o) { chk(); o.chk(); auto copy = *o.v; v->insert(v->end(), copy.begin(), copy.end()); }
  void Insert(int i, const T& x) { chk(); if (i < 0 || i > (int)v->size()) throw ArgumentOutOfRangeException(); v->insert(v->begin() + i, x); }
  int IndexOf(const T& x) const { chk(); for (size_t i = 0; i < v->size(); i++) if ((T)(*v)[i] == x) return (int)i; return -1; }
  bool Contains(const T& x) const { return IndexOf(x) >= 0; }
  bool Remove(const T& x) { int i = IndexOf(x); if (i < 0) return false; v->erase(v->begin() + i); return true; }
  void RemoveAt(int i) { chk(); if (i < 0 || i >= (int)v->size()) throw ArgumentOutOfRangeException(); v->erase(v->begin() + i); }
  void RemoveRange(int i, int n) { chk(); if (i < 0 || n < 0 || i + n > (int)v->size()) throw ArgumentOutOfRangeException(); v->erase(v->begin() + i, v->begin() + i + n); }
  void Clear() { chk(); v->clear(); }
  void Reverse() { chk(); std::reverse(v->begin(), v->end()); }
  void Sort() { chk(); std::stable_sort(v->begin(), v->end(), [](const Store<T>& a, const Store<T>& b) { return (T)a < (T)b; }); }
  void Sort(std::function<int(const T&, const T&)> cmp) { chk(); std::stable_sort(v->begin(), v->end(), [&](const Store<T>& a, const Store<T>& b) { return cmp(a, b) < 0; }); }
  Array<T> ToArray() const;
  T Find(std::function<bool(const T&)> pred) const { chk(); for (auto& x : *v) if (pred(x)) return x; return T(); }
  int FindIndex(std::function<bool(const T&)> pred) const { chk(); for (size_t i = 0; i < v->size(); i++) if (pred((*v)[i])) return (int)i; return -1; }
  bool Exists(std::function<bool(const T&)> pred) const { return FindIndex(pred) >= 0; }
  int RemoveAll(std::function<bool(const T&)> pred) { chk(); size_t n = v->size(); v->erase(std::remove_if(v->begin(), v->end(), [&](const Store<T>& x) { return pred(x); }), v->end()); return (int)(n - v->size()); }
  auto begin() { chk(); return v->begin(); }
  auto end() { chk(); return v->end(); }
  friend bool operator==(const List& a, const List& b) { return a.v == b.v; }
  friend bool operator!=(const List& a, const List& b) { return a.v != b.v; }
  friend bool operator==(const List& a, std::nullptr_t) { return !a.v; }
  friend bool operator!=(const List& a, std::nullptr_t) { return (bool)a.v; }
};

template <class T> class Array {
  std::shared_ptr<std::vector<Store<T>>> v;
  void chk() const { if (!v) throwNull(); }
public:
  using value_type = T;
  Array() {}
  Array(std::nullptr_t) {}
  static Array New(int n) { Array a; a.v = std::make_shared<std::vector<Store<T>>>(n > 0 ? n : 0); return a; }
  static Array Of(std::initializer_list<T> il) { Array a; a.v = std::make_shared<std::vector<Store<T>>>(); for (auto& x : il) a.v->push_back(x); return a; }
  static Array FromVector(std::vector<T> src) { Array a = New(0); for (auto& x : src) a.v->push_back(x); return a; }
  bool isNull() const { return !v; }
  int Length() const { chk(); return (int)v->size(); }
  Store<T>& operator[](int i) { chk(); if (i < 0 || i >= (int)v->size()) throw IndexOutOfRangeException(); return (*v)[i]; }
  const Store<T>& operator[](int i) const { chk(); if (i < 0 || i >= (int)v->size()) throw IndexOutOfRangeException(); return (*v)[i]; }
  auto begin() { chk(); return v->begin(); }
  auto end() { chk(); return v->end(); }
  std::vector<Store<T>>& vec() { chk(); return *v; }
  friend bool operator==(const Array& a, const Array& b) { return a.v == b.v; }
  friend bool operator!=(const Array& a, const Array& b) { return a.v != b.v; }
  friend bool operator==(const Array& a, std::nullptr_t) { return !a.v; }
  friend bool operator!=(const Array& a, std::nullptr_t) { return (bool)a.v; }
};
template <class T> Array<T> List<T>::ToArray() const { chk(); Array<T> a = Array<T>::New(0); for (auto& x : *v) a.vec().push_back(x); return a; }

// Generic "alive" check usable on anything nullable
template <class T> bool alive(const P<T>& p) { return !p.isNull(); }
inline bool alive(const String& s) { return !s.isNull(); }
template <class T> bool alive(const List<T>& l) { return !l.isNull(); }
template <class T> bool alive(const Array<T>& a) { return !a.isNull(); }

// ------------------------------------------------------------------ System.Math (banker's rounding like .NET)
double Math_Round(double v);
inline float Math_Abs(float v) { return std::fabs(v); }
inline int Math_Abs(int v) { return v < 0 ? -v : v; }

// DateTime (only what the game uses)
struct DateTime {
  int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
  static DateTime Now();
  long long get_Ticks() const;
  String ToShortDateString() const;
  String ToShortTimeString() const;
  String ToString() const;
};

// Debug log sink (engine prints to file/console)
void log(const char* fmt, ...);
void logFlush();   // write out anything the Vita log thread has not written yet
} // namespace cs

// Placeholders for a Unity/.NET feature the engine does not have yet (grep ENGINE_TODO to find them all).
//   statement:  ENGINE_TODO("AudioSource.mute = true");
//   value:      bool m = ENGINE_TODO_V("audioSource.mute", false);
#define ENGINE_TODO(what) ((void)0)
#define ENGINE_TODO_V(what, fallback) (fallback)
