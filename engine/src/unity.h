// The parts of UnityEngine that Don't Escape uses, re-created for the Vita.
// Translation rules (C# -> C++):
//   UnityEngine/game reference types -> P<T>, call members with ->
//   Unity properties -> get_x()/set_x(v) (e.g. transform->get_position()), except
//   Component::gameObject / Component::transform / GameObject::transform which are plain fields.
//   Value types (Vector2/3/4, Color, Rect, Bounds, ...) use plain fields (v.x, r.width).
#pragma once
#include "cs.h"
#include <typeinfo>
#include <type_traits>
#include <map>
#include <unordered_map>

using namespace cs;
class Object;
namespace engine { void forEachObject(const std::function<void(Object*)>& fn); }

struct JVal;
class FieldReader;
class JsonWriter;
struct ClassInfo;
class GameObject; class Component; class Transform; class Sprite; class Texture2D; class AudioClip;
class Camera; class Collider2D; class MonoBehaviour; class Animator; class RuntimeAnimatorController; class AnimationClip;

// ------------------------------------------------------------------ value types
struct Vector3;
struct Vector2 {
  float x = 0, y = 0;
  Vector2() {}
  Vector2(float x_, float y_) : x(x_), y(y_) {}
  Vector2(const Vector3& v);                       // implicit like C#
  Vector2 operator+(const Vector2& o) const { return { x + o.x, y + o.y }; }
  Vector2 operator-(const Vector2& o) const { return { x - o.x, y - o.y }; }
  Vector2 operator-() const { return { -x, -y }; }
  Vector2 operator*(float s) const { return { x * s, y * s }; }
  Vector2 operator/(float s) const { return { x / s, y / s }; }
  Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
  Vector2& operator-=(const Vector2& o) { x -= o.x; y -= o.y; return *this; }
  bool operator==(const Vector2& o) const { float dx = x - o.x, dy = y - o.y; return dx * dx + dy * dy < 9.99999944e-11f; }
  bool operator!=(const Vector2& o) const { return !(*this == o); }
  float get_magnitude() const { return std::sqrt(x * x + y * y); }
  static Vector2 get_zero() { return {}; }
  static Vector2 get_one() { return { 1, 1 }; }
  static float Distance(const Vector2& a, const Vector2& b) { return (a - b).get_magnitude(); }
  String ToString() const;
};
struct Vector3 {
  float x = 0, y = 0, z = 0;
  Vector3() {}
  Vector3(float x_, float y_, float z_ = 0) : x(x_), y(y_), z(z_) {}
  Vector3(const Vector2& v) : x(v.x), y(v.y), z(0) {}
  Vector3 operator+(const Vector3& o) const { return { x + o.x, y + o.y, z + o.z }; }
  Vector3 operator-(const Vector3& o) const { return { x - o.x, y - o.y, z - o.z }; }
  Vector3 operator-() const { return { -x, -y, -z }; }
  Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
  Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }
  Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
  Vector3& operator-=(const Vector3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
  bool operator==(const Vector3& o) const { float dx = x - o.x, dy = y - o.y, dz = z - o.z; return dx * dx + dy * dy + dz * dz < 9.99999944e-11f; }
  bool operator!=(const Vector3& o) const { return !(*this == o); }
  float get_magnitude() const { return std::sqrt(x * x + y * y + z * z); }
  static Vector3 get_zero() { return {}; }
  static Vector3 get_one() { return { 1, 1, 1 }; }
  static float Distance(const Vector3& a, const Vector3& b) { return (a - b).get_magnitude(); }
  String ToString() const;
};
inline Vector2::Vector2(const Vector3& v) : x(v.x), y(v.y) {}
inline Vector2 operator*(float s, const Vector2& v) { return v * s; }
inline Vector3 operator*(float s, const Vector3& v) { return v * s; }
struct Vector4 { float x = 0, y = 0, z = 0, w = 0; Vector4() {} Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Color {
  float r = 0, g = 0, b = 0, a = 0;
  Color() {}
  Color(float r_, float g_, float b_, float a_ = 1) : r(r_), g(g_), b(b_), a(a_) {}
  Color(const Vector4& v) : r(v.x), g(v.y), b(v.z), a(v.w) {}
  operator Vector4() const { return { r, g, b, a }; }
  bool operator==(const Color& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }
  bool operator!=(const Color& o) const { return !(*this == o); }
  static Color get_white() { return { 1, 1, 1, 1 }; } static Color get_black() { return { 0, 0, 0, 1 }; }
  static Color get_clear() { return { 0, 0, 0, 0 }; } static Color get_red() { return { 1, 0, 0, 1 }; }
};
struct Rect {
  float x = 0, y = 0, width = 0, height = 0;
  Rect() {}
  Rect(float x_, float y_, float w_, float h_) : x(x_), y(y_), width(w_), height(h_) {}
  bool Contains(const Vector2& p) const { return p.x >= x && p.x < x + width && p.y >= y && p.y < y + height; }
};
struct Bounds { Vector3 center, size; Vector3 get_center() const { return center; } Vector3 get_size() const { return size; } Vector3 get_min() const { return center - size * 0.5f; } Vector3 get_max() const { return center + size * 0.5f; } };
struct Quaternion { float x = 0, y = 0, z = 0, w = 1; static Quaternion get_identity() { return {}; } };
struct Matrix4x4 {
  float m[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }; // column-major like Unity
  static Matrix4x4 TRS(const Vector3& t, const Quaternion& q, const Vector3& s);
  Matrix4x4 operator*(const Matrix4x4& o) const;
};
struct Resolution { int width = 960, height = 540, refreshRate = 60; int get_width() const { return width; } int get_height() const { return height; } };
struct LayerMask {
  int value = 0;
  LayerMask() {} LayerMask(int v) : value(v) {}
  operator int() const { return value; }
  static int GetMask(std::initializer_list<String> names);
  static int GetMask(const String& a) { return GetMask({ a }); }
  static int GetMask(const String& a, const String& b) { return GetMask({ a, b }); }
  static int GetMask(const String& a, const String& b, const String& c) { return GetMask({ a, b, c }); }
  static int NameToLayer(const String& n);
};

enum class KeyCode { None = 0, Backspace = 8, Tab = 9, Return = 13, Escape = 27, Space = 32,
  A = 97, B, C, D, E, F, G, H, I, J, K, L, M, N, O, Pp, Q, R, S_, T, U, V, W, X, Y, Z,
  UpArrow = 273, DownArrow = 274, RightArrow = 275, LeftArrow = 276,
  RightShift = 303, LeftShift = 304, RightControl = 305, LeftControl = 306, RightAlt = 307, LeftAlt = 308,
  F1 = 282, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12 };
// KeyCode::P and KeyCode::S clash with cs::P / cs::S, so they are Pp and S_.

enum class FilterMode { Point = 0, Bilinear = 1, Trilinear = 2 };
enum class TextureFormat { Alpha8 = 1, ARGB4444 = 2, RGB24 = 3, RGBA32 = 4, ARGB32 = 5, RGB565 = 7, DXT1 = 10, DXT5 = 12 };
enum class CameraClearFlags { Skybox = 1, SolidColor = 2, Color = 2, Depth = 3, Nothing = 4 };
enum class SpriteMaskInteraction { None = 0, VisibleInsideMask = 1, VisibleOutsideMask = 2 };
enum class AudioReverbPreset { Off = 0, Generic, PaddedCell, Room, Bathroom, Livingroom, Stoneroom, Auditorium, Concerthall, Cave, Arena, Hangar, CarpettedHallway, Hallway, StoneCorridor, Alley, Forest, City, Mountains, Quarry, Plain, ParkingLot, SewerPipe, Underwater, Drugged, Dizzy, Psychotic, User };

// ------------------------------------------------------------------ UnityEngine.Object
class Object : public Obj {
public:
  int _id;
  String _name;
  bool _destroyed = false;
  bool _pendingDestroy = false;   // Destroy() called; gone at end of frame, gets no more Start/Update
  long long _srcId = 0;   // file ID in the scene/prefab data it was built from
  Object();
  Object(const Object& o);
#ifdef DE_LEAKCHECK
  ~Object() override;
#endif
  bool _isNullish() const override { return _destroyed; }
  virtual String get_name() const { return _name; }
  virtual void set_name(const String& n);
  virtual String ToString() const { return _name; }
  int GetInstanceID() const { return _id; }
  static void Destroy(const P<Object>& o, float t = 0);
  static void DontDestroyOnLoad(const P<Object>& o);
  static P<Object> Instantiate(const P<Object>& original);
  static P<GameObject> Instantiate(const P<GameObject>& original, const Vector3& pos, const Quaternion& rot);
  template <class T> static P<T> Instantiate(const P<T>& original) { return Instantiate(P<Object>(original)).template as<T>(); }
  template <class T> static P<T> FindObjectOfType();
  template <class T> static Array<P<T>> FindObjectsOfType();
};
// C# lets scripts write Destroy(x) / Instantiate(x) directly (inherited from Object)
inline void Destroy(const P<Object>& o, float t = 0) { Object::Destroy(o, t); }
inline void DontDestroyOnLoad(const P<Object>& o) { Object::DontDestroyOnLoad(o); }

// ------------------------------------------------------------------ GameObject / Component / Transform
// Component kinds: engine loops and GetComponent test this byte instead of dynamic_cast.
enum : uint8_t { CK_OTHER = 0, CK_TRANSFORM, CK_SPRITE, CK_MASK, CK_CAMERA, CK_COLLIDER, CK_ANIMATOR, CK_MB, CK_SORTGROUP };
template <class T> T* compAs(Component* c);
template <class T> T* _findComp(const std::vector<P<Component>>& comps);
struct ClassInfo;
const ClassInfo* _classInfoFor(const std::type_info& t);      // game class by C++ type (null if unknown)
bool _classIsA(const MonoBehaviour* mb, const ClassInfo* want);
class GameObject : public Object {
public:
  P<Transform> transform;
  std::vector<P<Component>> _comps;
  bool _active = true;
  int _layer = 0;
  String _tag = S("Untagged");
  int _scene = -1;        // scene slot, -2 = DontDestroyOnLoad, -3 = prefab template
  int _prefabIndex = -1;  // prefab template this object is the root of
  int _actStamp = -1; bool _actCache = false;   // activeInHierarchy cache (engine goActive): 1 = valid
  uint32_t _serial = 0; bool _listed = false;    // creation order; in g.objects (the scene's object list)
  GameObject();
  explicit GameObject(const String& name);
  P<Transform> get_transform() const { return transform; }
  P<GameObject> get_gameObject() { return P<GameObject>(this); }
  bool get_activeSelf() const { return _active; }
  bool get_activeInHierarchy() const;
  void SetActive(bool v);
  int get_layer() const { return _layer; }
  void set_layer(int l) { _layer = l; }
  String get_tag() const { return _tag; }
  void set_tag(const String& t);
  bool CompareTag(const String& t) const { return _tag == t; }
  template <class T> P<T> GetComponent() const { return P<T>(_findComp<T>(_comps)); }
  template <class T> Array<P<T>> GetComponents() const {
    Array<P<T>> a = Array<P<T>>::New(0);
    for (auto& c : _comps) if (!c.isNull()) if (T* t = compAs<T>(c.get())) a.vec().push_back(P<T>(t));
    return a;
  }
  template <class T> P<T> AddComponent();
  P<Component> _addComponent(Component* c);
  static P<GameObject> Find(const String& name);
  static P<GameObject> FindGameObjectWithTag(const String& tag);
  static Array<P<GameObject>> FindGameObjectsWithTag(const String& tag);
};

class Component : public Object {
public:
  ~Component() override;   // leaves the engine's per-kind lists
  uint8_t _kind = CK_OTHER;
  P<GameObject> gameObject;
  P<Transform> transform;
  P<GameObject> get_gameObject() const { return gameObject; }
  P<Transform> get_transform() const { return transform; }
  String get_tag() const { return gameObject->get_tag(); }
  template <class T> P<T> GetComponent() const { if (gameObject.isNull()) throwNull(); return gameObject->GetComponent<T>(); }
  template <class T> Array<P<T>> GetComponents() const { if (gameObject.isNull()) throwNull(); return gameObject->GetComponents<T>(); }
  String ToString() const override { return gameObject.get() ? gameObject->_name : _name; }
  String get_name() const override { return gameObject.get() ? gameObject->_name : _name; }   // Unity: a component's name is its GameObject's
  void set_name(const String& n) override;
  virtual void _onActiveChanged(bool) {}
  virtual Component* _cloneBuiltin() const { return nullptr; }   // built-in components copy themselves
};

class Transform : public Component {
public:
  Transform() { _kind = CK_TRANSFORM; }
  Vector3 _lp, _ls { 1, 1, 1 };
  mutable Vector3 _wp, _ws; mutable bool _wDirty = true;   // cached world position / lossy scale
  mutable uint32_t _wVer = 0;   // bumped each time the world values are recomputed (sprite quad cache)
  int _subGen = 0;   // bumped when anything below this transform is added, removed, renamed or re-parented
  void _updateWorld() const;
  void _invalidate() const;        // this and its children must recompute (a dirty node's children are always dirty)
  void _invalidateForce() const { _wDirty = false; _invalidate(); }
  Transform* _parent = nullptr;           // raw; the hierarchy owns children through GameObject lists
  std::vector<Transform*> _children;
  Vector3 get_position() const;
  void set_position(const Vector3& v);
  Vector3 get_localPosition() const { return _lp; }
  void set_localPosition(const Vector3& v) { if (v.x == _lp.x && v.y == _lp.y && v.z == _lp.z) return; _lp = v; _invalidate(); }
  Vector3 get_localScale() const { return _ls; }
  void set_localScale(const Vector3& v) { if (v.x == _ls.x && v.y == _ls.y && v.z == _ls.z) return; _ls = v; _invalidate(); }
  Vector3 get_lossyScale() const;
  P<Transform> get_parent() const { return P<Transform>(_parent); }
  void set_parent(const P<Transform>& p);
  void SetParent(const P<Transform>& p, bool worldPositionStays = true);
  P<Transform> Find(const String& name) const;
  int get_childCount() const { return (int)_children.size(); }
  P<Transform> GetChild(int i) const { if (i < 0 || i >= (int)_children.size()) throw ArgumentOutOfRangeException(); return P<Transform>(_children[i]); }
  void _detach();
};

class Behaviour : public Component {
public:
  bool _enabled = true;
  bool get_enabled() const { return _enabled; }
  virtual void set_enabled(bool v) { _enabled = v; }
  bool get_isActiveAndEnabled() const { return _enabled && gameObject.get() && gameObject->get_activeInHierarchy(); }
};

// ------------------------------------------------------------------ MonoBehaviour
class MonoBehaviour : public Behaviour {
public:
  MonoBehaviour() { _kind = CK_MB; }
  const ClassInfo* _cls = nullptr;
  bool _awoken = false, _started = false, _enabledCalled = false;
  void set_enabled(bool v) override;
  void Invoke(const String& method, float time);
  void InvokeRepeating(const String& method, float time, float repeatRate);
  void CancelInvoke();
  void CancelInvoke(const String& method);
  bool IsInvoking(const String& method) const;
  static void print(const String& s);
  static void print(const P<Object>& o);
  void _onActiveChanged(bool active) override;
  virtual void _load(FieldReader&) {}
  virtual void _clearRefs() {}
  virtual const ClassInfo* _getClassInfo() const { return nullptr; }
  virtual void _saveSerialized(JsonWriter&) {}   // fields Unity serializes (used by Instantiate)
};

// Physics bodies are not simulated (the game only uses colliders as click areas); kept so scripts compile.
class Rigidbody2D : public Component {
public:
  Vector2 _velocity; bool _kinematic = true;
  Vector2 get_velocity() const { return _velocity; } void set_velocity(const Vector2& v) { _velocity = v; }
  bool get_isKinematic() const { return _kinematic; } void set_isKinematic(bool k) { _kinematic = k; }
  void MovePosition(const Vector2& p) { if (transform.get()) transform->set_position(Vector3(p.x, p.y, transform->get_position().z)); }
};

// ------------------------------------------------------------------ assets
class Texture : public Object {
public:
  int _w = 0, _h = 0; FilterMode _filter = FilterMode::Point;
  int get_width() const { return _w; }
  int get_height() const { return _h; }
  void set_filterMode(FilterMode f) { _filter = f; }
  FilterMode get_filterMode() const { return _filter; }
};
class Texture2D : public Texture {
public:
  int _texIndex = -1;          // index into textures.json, -1 = runtime texture
  std::vector<uint8_t> _pixels; // RGBA for runtime textures (screenshots)
  unsigned _gpu = 0; bool _dirty = false;
  Texture2D() {}
  Texture2D(int w, int h) { _w = w; _h = h; _pixels.assign((size_t)w * h * 4, 0); _dirty = true; }
  Texture2D(int w, int h, int /*format*/, bool /*mip*/) : Texture2D(w, h) {}
  Texture2D(int w, int h, TextureFormat /*format*/, bool /*mip*/) : Texture2D(w, h) {}
  void ReadPixels(const Rect& src, int dx, int dy, bool recalc = false);
  void Apply() { _dirty = true; }
};
class RenderTexture : public Texture {
public:
  RenderTexture(int w, int h, int depth) { _w = w; _h = h; (void)depth; }
  static P<RenderTexture> _active;
  static void set_active(const P<RenderTexture>& r) { _active = r; }
  static P<RenderTexture> get_active() { return _active; }
};
class Sprite : public Object {
public:
  int _index = -1;            // index into sprites.json, -1 = created at runtime
  P<Texture2D> _tex;
  Rect _rect; Vector2 _pivotN; float _ppu = 100;
  Rect get_rect() const { return _rect; }
  Vector2 get_pivot() const { return { _pivotN.x * _rect.width, _pivotN.y * _rect.height }; } // pixels, like Unity
  P<Texture2D> get_texture() const { return _tex; }
  Bounds get_bounds() const;
  static P<Sprite> Create(const P<Texture2D>& t, const Rect& r, const Vector2& pivot, float ppu = 100);
};
class AudioClip : public Object {
public:
  int _index = -1; float _length = 0; int _channels = 2, _freq = 44100;
  float get_length() const { return _length; }
};
class TextAsset : public Object {
public:
  int _index = -1; String _text;
  String get_text() const { return _text; }
};
class Shader : public Object { public: static P<Shader> Find(const String& name); };
// _blend: how sprites using the material are drawn. The game's two custom materials only survive as names
// (AssetRipper exports shader stubs): MultiplyMaterial tints the scene (dusk/dawn), OverlayMaterial adds light (glows, god rays).
class Material : public Object { public: P<Shader> _shader; int _blend = 0; Material(const P<Shader>& s) : _shader(s) {} };
class AnimationClip : public Object { public: int _index = -1; float get_length() const; };
class RuntimeAnimatorController : public Object { public: int _index = -1; };

// ------------------------------------------------------------------ rendering components
class Renderer : public Component {
public:
  bool _enabled = true;
  int _sortingLayer = 0, _sortingOrder = 0;
  P<Material> _material;
  bool get_enabled() const { return _enabled; }
  void set_enabled(bool v) { _enabled = v; }
  void set_material(const P<Material>& m) { _material = m; }
  P<Material> get_material() const { return _material; }
  int get_sortingOrder() const { return _sortingOrder; }
  void set_sortingOrder(int o) { _sortingOrder = o; }
  virtual Bounds get_bounds() const;
};
class SpriteRenderer : public Renderer {
public:
  SpriteRenderer() { _kind = CK_SPRITE; }
  int _sortPos = -1; unsigned _sortStamp = 0;   // place in last frame's sorted sprite list
  int _slKey = -2147483647 - 1, _slOrder = 0;   // cached order of _sortingLayer
  // screen quad per camera, reused while nothing it depends on changed (engine cachedQuad)
  struct QuadCache { const void* cam = nullptr; const void* tr = nullptr; const void* sp = nullptr; const void* tex = nullptr;
    float ox = 0, oy = 0, left = 0, top = 0, ppu = 0; uint32_t wVer = 0; int tw = 0, th = 0, filt = 0; bool fx = false, fy = false, ok = false;
    float x0 = 0, y0 = 0, x1 = 0, y1 = 0, u0 = 0, v0 = 0, u1 = 0, v1 = 0; int texIndex = -1; bool linear = false; };
  QuadCache _qc[2]; uint8_t _qcNext = 0;
  P<Sprite> _sprite; Color _color { 1, 1, 1, 1 }; bool _flipX = false, _flipY = false;
  SpriteMaskInteraction _mask = SpriteMaskInteraction::None;
  P<Sprite> get_sprite() const { return _sprite; }
  void set_sprite(const P<Sprite>& s) { _sprite = s; }
  Color get_color() const { return _color; }
  void set_color(const Color& c) { _color = c; }
  bool get_flipX() const { return _flipX; } void set_flipX(bool v) { _flipX = v; }
  bool get_flipY() const { return _flipY; } void set_flipY(bool v) { _flipY = v; }
  void set_maskInteraction(SpriteMaskInteraction m) { _mask = m; }
  Bounds get_bounds() const override;
};
class SpriteMask : public Renderer {
public:
  SpriteMask() { _kind = CK_MASK; }
  P<Sprite> _sprite; float _cutoff = 0.2f;
  void set_sprite(const P<Sprite>& s) { _sprite = s; }
  P<Sprite> get_sprite() const { return _sprite; }
};

class Camera : public Behaviour {
public:
  Camera() { _kind = CK_CAMERA; }
  bool _ortho = true; float _size = 0.625f; float _depth = 0; int _mask = -1;
  CameraClearFlags _clear = CameraClearFlags::SolidColor; Color _bg;
  Rect _rect { 0, 0, 1, 1 };
  P<RenderTexture> _target;
  bool _customProj = false; Matrix4x4 _proj;
  static P<Camera> get_main();
  bool get_orthographic() const { return _ortho; } void set_orthographic(bool v) { _ortho = v; }
  float get_orthographicSize() const { return _size; } void set_orthographicSize(float s) { _size = s; }
  float get_depth() const { return _depth; } void set_depth(float d) { _depth = d; }
  int get_cullingMask() const { return _mask; } void set_cullingMask(int m) { _mask = m; }
  void set_clearFlags(CameraClearFlags f) { _clear = f; }
  void set_backgroundColor(const Color& c) { _bg = c; }
  Rect get_rect() const { return _rect; } void set_rect(const Rect& r) { _rect = r; }
  void set_targetTexture(const P<RenderTexture>& t) { _target = t; }
  P<RenderTexture> get_targetTexture() const { return _target; }
  Vector3 ScreenToWorldPoint(const Vector3& p) const;
  Vector3 WorldToScreenPoint(const Vector3& p) const;
  void Render();
  Matrix4x4 get_projectionMatrix() const { return _proj; }
  void set_projectionMatrix(const Matrix4x4& m) { _proj = m; _customProj = true; }
  void ResetProjectionMatrix() { _customProj = false; }
  // pixel scale helpers
  float _viewW() const; float _viewH() const;
};

// ------------------------------------------------------------------ physics 2D (point queries only)
class Collider2D : public Behaviour {
public:
  Collider2D() { _kind = CK_COLLIDER; }
  virtual void _worldBox(float& x0, float& y0, float& x1, float& y1) const;   // for quick rejects
  bool _trigger = false; Vector2 _offset;
  void set_isTrigger(bool v) { _trigger = v; } bool get_isTrigger() const { return _trigger; }
  void set_offset(const Vector2& o) { _offset = o; } Vector2 get_offset() const { return _offset; }
  virtual bool _contains(const Vector2& worldPoint) const = 0;
  virtual bool _segment(const Vector2& a, const Vector2& b, float& t) const; // first hit along a->b
  Bounds get_bounds() const;
  virtual void _localBounds(Vector2& mn, Vector2& mx) const = 0;
};
class BoxCollider2D : public Collider2D {
public:
  Vector2 _size { 1, 1 };
  void set_size(const Vector2& s) { _size = s; } Vector2 get_size() const { return _size; }
  bool _contains(const Vector2& p) const override;
  void _localBounds(Vector2& mn, Vector2& mx) const override;
};
class CircleCollider2D : public Collider2D {
public:
  void _worldBox(float& x0, float& y0, float& x1, float& y1) const override;
  float _radius = 0.5f;
  bool _contains(const Vector2& p) const override;
  void _localBounds(Vector2& mn, Vector2& mx) const override;
};
class PolygonCollider2D : public Collider2D {
public:
  mutable bool _bValid = false; mutable Vector2 _bMin, _bMax;   // path bounds without offset (SetPath clears)
  std::vector<std::vector<Vector2>> _paths;
  int get_pathCount() const { return (int)_paths.size(); }
  void set_pathCount(int n) { _paths.resize(n < 0 ? 0 : n); }
  Array<Vector2> GetPath(int i) const;
  void SetPath(int i, const Array<Vector2>& pts);
  bool _contains(const Vector2& p) const override;
  void _localBounds(Vector2& mn, Vector2& mx) const override;
};
struct RaycastHit2D {
  P<Collider2D> _collider; Vector2 point; float fraction = 0, distance = 0;
  P<Collider2D> get_collider() const { return _collider; }
  explicit operator bool() const { return !_collider.isNull(); }
};
struct Physics2D {
  static RaycastHit2D Linecast(const Vector2& a, const Vector2& b, int layerMask = -5);
  static Array<RaycastHit2D> LinecastAll(const Vector2& a, const Vector2& b, int layerMask = -5);
};

// ------------------------------------------------------------------ animation
struct AnimatorStateInfo { float _normalizedTime = 0, _length = 0; int _hash = 0; String _name;
  float get_normalizedTime() const { return _normalizedTime; } float get_length() const { return _length; }
  bool IsName(const String& n) const { return _name == n; } };
struct AnimatorClipInfo { P<AnimationClip> _clip; float weight = 1; P<AnimationClip> get_clip() const { return _clip; } };
class Animator : public Behaviour {
public:
  Animator() { _kind = CK_ANIMATOR; }
  int _ctrl = -1;              // controllers.json index
  int _state = -1; float _time = 0; float _speed = 1; bool _inited = false;
  int _lastEventFrame = -1;
  int _fromClip = -1; float _fromTime = 0, _fromEnd = 0, _fromSp = 1;   // during an exit-time transition: the old clip, whose events still fire until the blend ends
  int _tClip = -1, _tGen = -1; GameObject* _tRoot = nullptr; std::vector<GameObject*> _tPP, _tFC;   // animated objects of the current clip
  void Play(const String& stateName, int layer = -1, float normalizedTime = -1e30f);
  void set_speed(float s) { _speed = s; }
  float get_speed() const { return _speed; }
  AnimatorStateInfo GetCurrentAnimatorStateInfo(int layer) const;
  Array<AnimatorClipInfo> GetCurrentAnimatorClipInfo(int layer) const;
  P<RuntimeAnimatorController> get_runtimeAnimatorController() const;
};

// ------------------------------------------------------------------ audio
class AudioSource : public Behaviour {
public:
  P<AudioClip> _clip; float _volume = 1, _pitch = 1, _pan = 0; bool _loop = false, _playOnAwake = false, _mute = false;
  bool _ignorePause = false, _ignoreVolume = false;
  int _voice = -1;              // mixer voice handle
  AudioSource() {}
  P<AudioClip> get_clip() const { return _clip; } void set_clip(const P<AudioClip>& c) { _clip = c; }
  float get_volume() const { return _volume; } void set_volume(float v);
  float get_pitch() const { return _pitch; } void set_pitch(float p);
  float get_panStereo() const { return _pan; } void set_panStereo(float p);
  bool get_loop() const { return _loop; } void set_loop(bool l);
  void set_ignoreListenerPause(bool v) { _ignorePause = v; }
  void set_ignoreListenerVolume(bool v) { _ignoreVolume = v; }
  bool get_isPlaying() const;
  float get_time() const; void set_time(float t);
  void Play(); void PlayDelayed(float d); void Stop();
  void PlayOneShot(const P<AudioClip>& clip, float volumeScale = 1);
};
class AudioListener : public Behaviour {
public:
  static float _volume; static bool _pause;
  static void set_volume(float v) { _volume = v; } static float get_volume() { return _volume; }
  static void set_pause(bool p); static bool get_pause() { return _pause; }
};
class AudioReverbFilter : public Behaviour {
public:
  AudioReverbPreset _preset = AudioReverbPreset::Off;
  AudioReverbPreset get_reverbPreset() const { return _preset; }
  void set_reverbPreset(AudioReverbPreset p) { _preset = p; }
};
class GUILayer : public Behaviour {};
class SortingGroup : public Behaviour { public: SortingGroup() { _kind = CK_SORTGROUP; } int _sortingOrder = 0; void set_sortingOrder(int o) { _sortingOrder = o; } int get_sortingOrder() const { return _sortingOrder; } };
class FlareLayer : public Behaviour {};

// ------------------------------------------------------------------ static services
struct Mathf {
  static constexpr float PI = 3.14159274f;
  static float Abs(float v) { return std::fabs(v); }
  static int Abs(int v) { return v < 0 ? -v : v; }
  static float Pow(float a, float b) { return std::pow(a, b); }
  static float Sqrt(float v) { return std::sqrt(v); }
  static float Floor(float v) { return std::floor(v); }
  static float Ceil(float v) { return std::ceil(v); }
  static float Round(float v) { return (float)Math_Round(v); }
  static int CeilToInt(float v) { return (int)std::ceil(v); }
  static int FloorToInt(float v) { return (int)std::floor(v); }
  static int RoundToInt(float v) { return (int)Math_Round(v); }
  static float Min(float a, float b) { return a < b ? a : b; }
  static int Min(int a, int b) { return a < b ? a : b; }
  static float Max(float a, float b) { return a > b ? a : b; }
  static int Max(int a, int b) { return a > b ? a : b; }
  static float Clamp(float v, float a, float b) { return v < a ? a : v > b ? b : v; }
  static int Clamp(int v, int a, int b) { return v < a ? a : v > b ? b : v; }
  static float Clamp01(float v) { return Clamp(v, 0.f, 1.f); }
  static float Lerp(float a, float b, float t) { return a + (b - a) * Clamp01(t); }
  static float Sin(float v) { return std::sin(v); } static float Cos(float v) { return std::cos(v); }
  static float Sign(float v) { return v >= 0 ? 1.f : -1.f; }
};
struct Random {
  static int Range(int a, int b);         // max exclusive
  static float Range(float a, float b);   // max inclusive
  static float get_value();
  static void set_seed(int s);
  static int get_seed();
};
struct Time {
  static float _dt, _time; static int _frame;
  static float get_deltaTime() { return _dt; }
  static float get_time() { return _time; }
  static int get_frameCount() { return _frame; }
};
struct Input {
  static bool GetKey(KeyCode k);
  static KeyCode _keyFromName(const String& n);
  static bool GetKey(const String& n) { return GetKey(_keyFromName(n)); }
  static bool GetKeyDown(const String& n) { return GetKeyDown(_keyFromName(n)); }
  static bool GetKeyUp(const String& n) { return GetKeyUp(_keyFromName(n)); }
  static bool GetKeyDown(KeyCode k);
  static bool GetKeyUp(KeyCode k);
  static bool GetMouseButton(int b);
  static bool GetMouseButtonDown(int b);
  static bool GetMouseButtonUp(int b);
  static Vector3 get_mousePosition();
};
struct Screen {
  static int get_width(); static int get_height();
  static bool get_fullScreen() { return true; }
  static void set_fullScreen(bool) {}
  static Resolution get_currentResolution() { Resolution r; r.width = get_width(); r.height = get_height(); return r; }
  static Array<Resolution> get_resolutions() { return Array<Resolution>::Of({ get_currentResolution() }); }
  static void SetResolution(int, int, bool) {}
};
struct Cursor { static void set_visible(bool) {} };
struct SystemInfo { static String get_graphicsDeviceVersion() { return S("OpenGL ES 2.0 (Vita)"); } };
struct Application {
  static void Quit();
  static String get_persistentDataPath();
  static void set_targetFrameRate(int) {}
  static String get_version() { return S("1.0"); }
};
struct PlayerPrefs {
  static void SetInt(const String& k, int v); static int GetInt(const String& k, int def = 0);
  static void SetFloat(const String& k, float v); static float GetFloat(const String& k, float def = 0);
  static void SetString(const String& k, const String& v); static String GetString(const String& k, const String& def = String::Empty);
  static bool HasKey(const String& k); static void DeleteKey(const String& k); static void Save();
};
struct Debug {
  static void Log(const String& s); static void LogWarning(const String& s); static void LogError(const String& s);
  static void Log(const P<Object>& o) { Log(o.isNull() ? S("Null") : o->ToString()); }
};
struct Scene { int _index = -1; String get_name() const; int get_buildIndex() const { return _index; } };
struct SceneManager {
  static Scene GetActiveScene();
  static void LoadScene(int index);
  static void LoadScene(const String& name);
};
struct Resources {
  static P<Object> Load(const String& path);
  template <class T> static P<T> Load(const String& path) { return _load(path, _kind<T>()).template as<T>(); }
  template <class T> static Array<P<T>> LoadAll(const String& path) {
    Array<P<T>> out = Array<P<T>>::New(0);
    for (auto& o : _loadAll(path, _kind<T>())) if (T* t = dynamic_cast<T*>(o.get())) out.vec().push_back(P<T>(t));
    return out;
  }
  template <class T> static Array<P<T>> FindObjectsOfTypeAll() {
    Array<P<T>> out = Array<P<T>>::New(0);
    engine::forEachObject([&](Object* o) { if (T* t = dynamic_cast<T*>(o)) out.vec().push_back(P<T>(t)); });
    return out;
  }
  template <class T> static const char* _kind() {
    if (std::is_base_of_v<Sprite, T>) return "sprite"; if (std::is_base_of_v<Texture2D, T>) return "tex";
    if (std::is_base_of_v<AudioClip, T>) return "audio"; if (std::is_base_of_v<TextAsset, T>) return "text";
    if (std::is_base_of_v<GameObject, T>) return "prefab"; if (std::is_base_of_v<RuntimeAnimatorController, T>) return "ctrl";
    return "";
  }
  static P<Object> _load(const String& path, const char* kind);
  static std::vector<P<Object>> _loadAll(const String& path, const char* kind);
};
struct ImageConversion {
  static Array<uint8_t> EncodeToPNG(const P<Texture2D>& t);
  static bool LoadImage(const P<Texture2D>& t, const Array<uint8_t>& data);
};

// ------------------------------------------------------------------ System.Text
struct Encoding {
  struct UTF8Encoding {
    Array<uint8_t> GetBytes(const String& s) const { std::string b = s.utf8(); Array<uint8_t> a = Array<uint8_t>::New((int)b.size()); for (size_t i = 0; i < b.size(); i++) a[(int)i] = (uint8_t)b[i]; return a; }
    String GetString(const Array<uint8_t>& bytes) const { Array<uint8_t> a = bytes; std::string b(a.vec().begin(), a.vec().end()); return String::FromUtf8(b.data(), b.size()); }
  };
  static UTF8Encoding get_UTF8() { return {}; }   // C#: Encoding.UTF8.GetBytes(s) -> Encoding::get_UTF8().GetBytes(s)
};

// ------------------------------------------------------------------ System.IO (save files)
class FileStream; enum class FileMode : int;
struct File {
  static P<FileStream> Open(const String& path, FileMode mode);
  static bool Exists(const String& path);
  static void Delete(const String& path);
  static void WriteAllBytes(const String& path, const Array<uint8_t>& data);
  static Array<uint8_t> ReadAllBytes(const String& path);
};

// ------------------------------------------------------------------ templates needing engine internals
namespace engine {
  void forEachObject(const std::function<void(Object*)>& fn); // all live scene objects and components
  void registerComponent(const P<GameObject>& go, Component* c);
}
template <class T> P<T> GameObject::AddComponent() { T* c = new T(); engine::registerComponent(P<GameObject>(this), c); return P<T>(c); }
template <class T> P<T> Object::FindObjectOfType() {
  P<T> found;
  engine::forEachObject([&](Object* o) { if (found.isNull()) if (T* t = dynamic_cast<T*>(o)) { if (auto* c = dynamic_cast<Component*>(o)) { if (!c->gameObject.get() || !c->gameObject->get_activeInHierarchy()) return; } found = P<T>(t); } });
  return found;
}
template <class T> Array<P<T>> Object::FindObjectsOfType() {
  Array<P<T>> out = Array<P<T>>::New(0);
  engine::forEachObject([&](Object* o) { if (T* t = dynamic_cast<T*>(o)) { if (auto* c = dynamic_cast<Component*>(o)) { if (!c->gameObject.get() || !c->gameObject->get_activeInHierarchy()) return; } out.vec().push_back(P<T>(t)); } });
  return out;
}

// ------------------------------------------------------------------ fast component type tests
template <class T> constexpr uint8_t _compKind() {
  if constexpr (std::is_same_v<T, Transform>) return CK_TRANSFORM;
  else if constexpr (std::is_same_v<T, SpriteRenderer>) return CK_SPRITE;
  else if constexpr (std::is_same_v<T, SpriteMask>) return CK_MASK;
  else if constexpr (std::is_same_v<T, Camera>) return CK_CAMERA;
  else if constexpr (std::is_base_of_v<Collider2D, T>) return CK_COLLIDER;
  else if constexpr (std::is_same_v<T, Animator>) return CK_ANIMATOR;
  else if constexpr (std::is_base_of_v<MonoBehaviour, T>) return CK_MB;
  else if constexpr (std::is_same_v<T, SortingGroup>) return CK_SORTGROUP;
  else return CK_OTHER;
}
// T* if the component is a T, else null: same answer as dynamic_cast
template <class T> T* compAs(Component* c) {
  if (!c) return nullptr;
  constexpr uint8_t k = _compKind<T>();
  if constexpr (k != CK_OTHER) {
    if (c->_kind != k) return nullptr;
    // the kind alone decides it for the kind's own class; subclasses (BoxCollider2D, script classes) still need the real test
    if constexpr (std::is_same_v<T, Collider2D> || std::is_same_v<T, MonoBehaviour> ||
                  (!std::is_base_of_v<Collider2D, T> && !std::is_base_of_v<MonoBehaviour, T>)) return static_cast<T*>(c);
  }
  return dynamic_cast<T*>(c);
}
// first component that is a T (Unity order), like the old dynamic_cast loop
template <class T> T* _findComp(const std::vector<P<Component>>& comps) {
  if constexpr (std::is_base_of_v<MonoBehaviour, T> && !std::is_same_v<T, MonoBehaviour>) {
    static const ClassInfo* want = _classInfoFor(typeid(T));
    if (want) {
      for (auto& c : comps) { Component* x = c.get(); if (x && x->_kind == CK_MB && _classIsA(static_cast<MonoBehaviour*>(x), want)) return static_cast<T*>(static_cast<MonoBehaviour*>(x)); }
      return nullptr;
    }
  }
  for (auto& c : comps) if (T* t = compAs<T>(c.get())) return t;
  return nullptr;
}
