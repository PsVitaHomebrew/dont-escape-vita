// Core runtime: data, scenes, object lifetime, Unity message order, timers, mouse events, animation, drawing lists.
#include "engine.h"
#include "registry.h"
#include "json.h"
#include <cstdio>
#include <cstdarg>
#include <map>
#include <set>
#include "inflate.h"
#ifdef VITA
#include <zlib.h>
#endif
#include "audio.h"
#include <chrono>
// ---- profiling: time per frame phase and per script class (printed by engineProfileReport)
static double profPhase[8]; static const char* profNames[8] = { "scene load", "mouse", "Start", "Update", "timers", "animators", "LateUpdate", "destroy" };
static std::map<std::string, double> profClass; static int profFrames = 0;
#ifdef VITA
static const bool profClasses = false;   // per-script timing costs too much on the Vita; phases only
#else
static const bool profClasses = true;
#endif
#ifdef VITA
#include <psp2/kernel/processmgr.h>
static double nowMs() { return sceKernelGetProcessTimeWide() / 1000.0; }   // the Vita's own microsecond clock
#else
static double nowMs() { return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
#endif
// Hands the per-phase totals since the last call to the caller (Vita perf log) and starts counting again.
int engineTakeProfile(double out[8], const char* names[8]) {
  int n = profFrames;
  for (int i = 0; i < 8; i++) { out[i] = profPhase[i]; names[i] = profNames[i]; profPhase[i] = 0; }
  profFrames = 0; return n;
}
void engineProfileReport() {
  if (!profFrames) return; cs::log("profile over %d frames (ms per frame):", profFrames);
  for (int i = 0; i < 8; i++) cs::log("  %-11s %.3f", profNames[i], profPhase[i] / profFrames);
  std::vector<std::pair<double, std::string>> v; for (auto& kv : profClass) v.push_back({ kv.second, kv.first }); std::sort(v.rbegin(), v.rend());
  for (size_t i = 0; i < v.size() && i < 15; i++) cs::log("  %-34s %.3f", v[i].second.c_str(), v[i].first / profFrames);
}

namespace cs { void setLogFile(const char* path); }
void gameStaticInit();

// ======================================================================= registry
static std::map<std::string, const ClassInfo*>& classes() { static std::map<std::string, const ClassInfo*> m; return m; }
void registerClass(const ClassInfo* ci) { classes()[ci->name] = ci; }
static const ClassInfo* baseOf(const ClassInfo* c) {
  if (!c->_baseDone) { c->_baseInfo = (c->base && *c->base && strcmp(c->base, "MonoBehaviour")) ? findClass(c->base) : nullptr; c->_baseDone = true; }
  return c->_baseInfo;
}
bool _classIsA(const MonoBehaviour* mb, const ClassInfo* want) {
  const ClassInfo* c = mb->_cls ? mb->_cls : mb->_getClassInfo();
  for (int depth = 0; c && depth < 16; depth++, c = baseOf(c)) if (c == want) return true;
  return false;
}
// C++ type -> generated ClassInfo, by the type's name ("22ObjectActionController" on GCC, "class X" on MSVC)
const ClassInfo* _classInfoFor(const std::type_info& t) {
  const char* n = t.name();
  if (!strncmp(n, "class ", 6)) n += 6; else if (!strncmp(n, "struct ", 7)) n += 7;
  else { const char* p = n; while (*p >= '0' && *p <= '9') p++; if (p == n) return nullptr; size_t len = (size_t)atoi(n); if (strlen(p) != len) return nullptr; n = p; }
  return findClass(n);
}
const ClassInfo* findClass(const char* name) { auto it = classes().find(name); return it == classes().end() ? nullptr : it->second; }

using namespace engine;

// ======================================================================= state
static int g_sceneLoads = 0;
struct Timer { P<MonoBehaviour> mb; std::string name; float at; float repeat; bool rep; bool dead = false; };
struct DelayedDestroy { P<Object> o; float at; };
struct Voice { int clip; float start; float pitch; bool loop; bool oneShot; P<AudioSource> src; float volume; int mix = -1; };

struct G {
  std::string data, save;
  JVal manifest, textures, sprites, audio, texts, anims, ctrls, prefabs, resources, assetIndex;
  std::vector<P<Sprite>> spriteObjs; std::vector<P<Texture2D>> texObjs; std::vector<P<AudioClip>> audioObjs;
  std::vector<P<TextAsset>> textObjs; std::vector<P<GameObject>> prefabObjs; std::vector<P<AnimationClip>> clipObjs;
  std::vector<P<RuntimeAnimatorController>> ctrlObjs;
  std::map<int, int> sortingLayerOrder;
  std::vector<std::string> layerNames;
  std::vector<P<GameObject>> objects;        // every live GameObject (scenes, DontDestroyOnLoad, runtime)
  std::vector<P<MonoBehaviour>> behaviours;  // every live script, sorted by execution order when needed
  bool behavioursDirty = false;
  std::vector<Timer> timers;
  std::vector<P<Object>> destroyQueue;
  std::vector<P<GameObject>> zombies; std::vector<P<Component>> zombieComps;   // destroyed during play: cycles broken at the next scene load
  std::vector<DelayedDestroy> delayed;
  int activeScene = -1, pendingScene = -1;
  InputState in, prev;
  P<GameObject> hover, pressed;
  bool viewer = false, quit = false;
  int scriptErrors = 0;
  std::map<std::string, std::string> prefs; bool prefsDirty = false; float prefsTimer = 0;
  std::vector<Voice> voices;
  float audioClock = 0;
  int nextId = 1;
  int gen = 0;            // bumped on scene load: the Find index is rebuilt
  int camGen = 0;         // bumped when the main camera may have changed (activation, destroy, tag, new cameras)
} g;

static void indexAdd(GameObject* go); static void indexRename(GameObject* go, const String& oldName); static void indexRetag(GameObject* go, const String& oldTag); static void indexDrop(GameObject* go);
static std::string readFile(const std::string& path) {
  FILE* f = fopen(path.c_str(), "rb"); if (!f) return std::string();
  fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
  std::string s; s.resize(n > 0 ? n : 0); if (n > 0) fread(&s[0], 1, n, f); fclose(f); return s;
}
static bool loadJson(const std::string& name, JVal& out) {
  std::string s = readFile(g.data + "/" + name);
  if (s.empty()) { cs::log("missing data file %s", name.c_str()); return false; }
  return JParser::parse(s.data(), s.size(), out);
}

// ======================================================================= script calls with Unity-style error handling
static void reportError(MonoBehaviour* mb, const char* what, const char* msg) {
  g.scriptErrors++;
  if (g.scriptErrors < 400) cs::log("[script error] %s.%s on '%s': %s", mb && mb->_cls ? mb->_cls->name : "?", what, mb && mb->gameObject.get() ? mb->gameObject->_name.utf8().c_str() : "?", msg);
}
template <class F> static void guarded(MonoBehaviour* mb, const char* what, F&& f) {
  try { f(); }
  catch (const cs::Exception& e) { reportError(mb, what, e.what()); }
  catch (const std::exception& e) { reportError(mb, what, e.what()); }
}
static bool profSample = false;   // Vita: scripts are timed on 1 frame in 300 (engineTopScripts); that frame is left out of the stats
// After a hitch the Vita build times every script call for a while (engineArmCallTiming), so the next hitch names
// the scripts that caused it (engineSlowCalls): hitches tend to come from the same actions again.
static bool profTiming = false; static int profArmFrames = 0;
struct SlowCall { double ms; std::string name; };
static SlowCall slowest[3]; static int slowN = 0;
static void noteCall(double ms, const ClassInfo* cls, const char* what, const char* invokeName) {
  if (slowN == 3 && ms <= slowest[2].ms) return;
  std::string n = std::string(cls ? cls->name : "?") + "." + what + (invokeName ? std::string("(") + invokeName + ")" : std::string());
  int i = slowN < 3 ? slowN++ : 2;
  slowest[i] = { ms, n };
  while (i > 0 && slowest[i].ms > slowest[i - 1].ms) { std::swap(slowest[i], slowest[i - 1]); i--; }
}
void engineArmCallTiming(int frames) { if (frames > profArmFrames) profArmFrames = frames; }
bool engineFrameWasSampled() { return profSample; }
// the slowest script calls of the frame just run; false when calls were not being timed
bool engineSlowCalls(char* out, int n) {
  out[0] = 0; if (!profTiming) return false;
  int w = 0; for (int i = 0; i < slowN && w < n - 1; i++) w += snprintf(out + w, n - w, "%s%s %.1f ms", i ? ", " : "", slowest[i].name.c_str(), slowest[i].ms);
  return true;
}
static std::map<std::pair<const ClassInfo*, const char*>, double> profSampled; static int profSampledFrames = 0;
int engineTopScripts(char* out, int n) {
  std::vector<std::pair<double, std::string>> v;
  for (auto& kv : profSampled) v.push_back({ kv.second, std::string(kv.first.first ? kv.first.first->name : "?") + "." + kv.first.second });
  std::sort(v.rbegin(), v.rend());
  int w = 0; out[0] = 0;
  for (size_t i = 0; i < v.size() && i < 6 && w < n - 1; i++) w += snprintf(out + w, n - w, "%s%s %.2f", i ? ", " : "", v[i].second.c_str(), profSampledFrames ? v[i].first / profSampledFrames : 0);
  profSampled.clear(); profSampledFrames = 0;
  return w;
}
static void call(MonoBehaviour* mb, MsgFn fn, const char* what) {
  if (!fn) return;
  if (!profClasses) {
    if (!profSample && !profTiming) { guarded(mb, what, [&] { fn(mb); }); return; }
    double t0 = nowMs(); guarded(mb, what, [&] { fn(mb); }); double d = nowMs() - t0;
    if (profSample) profSampled[{ mb->_cls, what }] += d;
    if (profTiming) noteCall(d, mb->_cls, what, nullptr);
    return;
  }
  double t0 = nowMs(); guarded(mb, what, [&] { fn(mb); });
  if (mb->_cls) profClass[std::string(mb->_cls->name) + "." + what] += nowMs() - t0;
}

// ======================================================================= lifecycle helpers
static bool goActiveSlow(GameObject* go) { for (Transform* t = go->transform.get(); t; t = t->_parent) if (!t->gameObject.get() || !t->gameObject->_active) return false; return true; }
static bool goActive(GameObject* go) {
  if (go->_actStamp == 1) return go->_actCache;
  go->_actCache = goActiveSlow(go); go->_actStamp = 1; return go->_actCache;
}
// a subtree's active state may have changed (SetActive, re-parenting, destroy)
static void invalidateActive(Transform* t) { if (!t) return; if (t->gameObject.get()) t->gameObject->_actStamp = -1; for (Transform* c : t->_children) invalidateActive(c); }
// ---- per-kind component lists (cameras, colliders, sprites, masks, animators, sorting groups), in object
// creation order then component order: the order a walk over g.objects gave
static std::vector<Component*>* g_reg = new std::vector<Component*>[CK_SORTGROUP + 1];   // never freed: components outlive statics at exit
static bool g_regSorted[CK_SORTGROUP + 1] = { true, true, true, true, true, true, true, true, true };
static bool regTracked(uint8_t k) { return k == CK_CAMERA || k == CK_COLLIDER || k == CK_SPRITE || k == CK_MASK || k == CK_ANIMATOR || k == CK_SORTGROUP; }
static void regAdd(Component* c) {
  uint8_t k = c->_kind; if (!regTracked(k)) return;
  auto& v = g_reg[k];
  if (!v.empty() && v.back()->gameObject.get() && c->gameObject.get() && v.back()->gameObject->_serial > c->gameObject->_serial) g_regSorted[k] = false;
  v.push_back(c);
}
static void regRemove(Component* c) {
  uint8_t k = c->_kind; if (!regTracked(k)) return;
  auto& v = g_reg[k]; auto it = std::find(v.begin(), v.end(), c); if (it != v.end()) v.erase(it);
}
Component::~Component() { regRemove(this); }
static int compIndex(const Component* c) {
  GameObject* go = c->gameObject.get(); if (!go) return 0;
  for (size_t i = 0; i < go->_comps.size(); i++) if (go->_comps[i].get() == c) return (int)i;
  return 0;
}
static const std::vector<Component*>& reg(uint8_t k) {
  if (!g_regSorted[k]) {
    std::stable_sort(g_reg[k].begin(), g_reg[k].end(), [](Component* a, Component* b) {
      uint32_t sa = a->gameObject.get() ? a->gameObject->_serial : 0, sb = b->gameObject.get() ? b->gameObject->_serial : 0;
      if (sa != sb) return sa < sb; return compIndex(a) < compIndex(b); });
    g_regSorted[k] = true;
  }
  return g_reg[k];
}
static bool subtreeHasCamera(GameObject* go) {
  Transform* root = go->transform.get(); if (!root) return true;
  for (Component* c : g_reg[CK_CAMERA]) for (Transform* t = c->transform.get(); t; t = t->_parent) if (t == root) return true;
  return false;
}
// an object a per-frame pass should see (what the g.objects walk skipped: unlisted, prefab templates)
static inline GameObject* liveOwner(Component* c) { GameObject* go = c->gameObject.get(); return go && go->_listed && go->_scene != -3 && !go->_destroyed ? go : nullptr; }
// something under these transforms changed: Animators above it look their targets up again
static void bumpHier(Transform* t) { for (; t; t = t->_parent) t->_subGen++; }

static void awakeAndEnable(MonoBehaviour* mb) {
  if (g.viewer || !mb->_cls) return;
  if (!mb->_awoken) { mb->_awoken = true; call(mb, mb->_cls->Awake, "Awake"); }
  if (mb->_enabled && !mb->_enabledCalled && mb->gameObject.get() && goActive(mb->gameObject.get())) { mb->_enabledCalled = true; call(mb, mb->_cls->OnEnable, "OnEnable"); }
}
static void disable(MonoBehaviour* mb) {
  if (mb->_enabledCalled) { mb->_enabledCalled = false; if (mb->_cls && !g.viewer) call(mb, mb->_cls->OnDisable, "OnDisable"); }
}

static void onBecameActive(GameObject* go, bool active);
static void walkHierarchy(Transform* t, const std::function<void(GameObject*)>& fn) {
  if (!t || !t->gameObject.get()) return;
  fn(t->gameObject.get());
  auto kids = t->_children; for (Transform* c : kids) walkHierarchy(c, fn);
}
static void onBecameActive(GameObject* go, bool active) {
  // go's activeInHierarchy just changed to `active`; propagate to components in its subtree that are effectively affected
  walkHierarchy(go->transform.get(), [&](GameObject* o) {
    if (active && !goActive(o)) return;
    auto comps = o->_comps;
    for (auto& c : comps) if (c.get()) c->_onActiveChanged(active);
  });
}

void MonoBehaviour::_onActiveChanged(bool active) { if (active) awakeAndEnable(this); else disable(this); }
void MonoBehaviour::set_enabled(bool v) {
  if (v == _enabled) return;
  _enabled = v;
  if (!gameObject.get() || !goActive(gameObject.get())) return;
  if (v) awakeAndEnable(this); else disable(this);
}

bool GameObject::get_activeInHierarchy() const { return goActive(const_cast<GameObject*>(this)); }
static bool subtreeHasCamera(GameObject* go);
void GameObject::SetActive(bool v) {
  if (_active == v) return;
  if (subtreeHasCamera(this)) g.camGen++;
  bool before = goActive(this);
  _active = v; invalidateActive(transform.get());
  bool after = goActive(this);
  if (before != after) onBecameActive(this, after);
}

#ifdef DE_LEAKCHECK
#include <unordered_set>
#include <typeinfo>
static std::unordered_set<Object*>& liveSet() { static auto* s = new std::unordered_set<Object*>(); return *s; }   // never freed: objects outlive static destruction
Object::~Object() { liveSet().erase(this); }
void engineLiveDump(const char* path) {
  std::map<std::string, int> n;
  for (Object* o : liveSet()) {
    std::string k = typeid(*o).name();
    if (auto* mb = dynamic_cast<MonoBehaviour*>(o)) k = std::string("MB ") + (mb->_cls ? mb->_cls->name : "?");
    else if (auto* go = dynamic_cast<GameObject*>(o)) k = "GO " + o->_name.utf8();
    if (o->_destroyed) k = "[destroyed] " + k;
    n[k]++;
  }
  FILE* f = fopen(path, "w"); if (!f) return;
  for (auto& kv : n) fprintf(f, "%d\t%s\n", kv.second, kv.first.c_str());
  fclose(f);
}
#endif
Object::Object() { _id = g.nextId++;
#ifdef DE_LEAKCHECK
  liveSet().insert(this);
#endif
}
GameObject::GameObject() : GameObject(S("New Game Object")) {}
GameObject::GameObject(const String& name) {
  _name = name;
  Transform* t = new Transform();
  t->gameObject = P<GameObject>(this); t->transform = P<Transform>(t); t->_name = name;
  transform = P<Transform>(t);
  _comps.push_back(P<Component>(t));
  _scene = g.activeScene;
  static uint32_t serials = 0; _serial = ++serials;
  if (g.activeScene >= 0 || g.activeScene == -1) { g.objects.push_back(P<GameObject>(this)); indexAdd(this); _listed = true; }
}
void Object::set_name(const String& n) { String old = _name; _name = n; if (auto* go = dynamic_cast<GameObject*>(this)) { indexRename(go, old); bumpHier(go->transform.get()); } }
void Component::set_name(const String& n) { if (gameObject.get()) { bumpHier(gameObject->transform.get()); String old = gameObject->_name; gameObject->_name = n; indexRename(gameObject.get(), old); } _name = n; }
void GameObject::set_tag(const String& t) { String old = _tag; _tag = t; indexRetag(this, old); g.camGen++; }

void engine::registerComponent(const P<GameObject>& go, Component* c) {
  c->gameObject = go; c->transform = go->transform; c->_name = go->_name;
  go->_comps.push_back(P<Component>(c)); regAdd(c);
  if (dynamic_cast<Camera*>(c)) g.camGen++;
  if (auto* mb = dynamic_cast<MonoBehaviour*>(c)) {
    if (!mb->_cls) mb->_cls = mb->_getClassInfo();
    g.behaviours.push_back(P<MonoBehaviour>(mb)); g.behavioursDirty = true;
    if (goActive(go.get())) awakeAndEnable(mb);
  }
}
P<Component> GameObject::_addComponent(Component* c) { registerComponent(P<GameObject>(this), c); return P<Component>(c); }

void engine::forEachObject(const std::function<void(Object*)>& fn) {
  auto objs = g.objects;
  for (auto& go : objs) { if (go.isNull()) continue; fn(go.get()); for (auto& c : go->_comps) if (!c.isNull()) fn(c.get()); }
}

// ======================================================================= transforms
// World position/scale are cached; anything that changes a transform or its parent calls _invalidate().
void Transform::_invalidate() const { if (_wDirty) return; _wDirty = true; for (Transform* c : _children) c->_invalidate(); }
void Transform::_updateWorld() const {
  if (!_wDirty) return;
  if (_parent) {
    _parent->_updateWorld(); const Vector3& pp = _parent->_wp; const Vector3& ps = _parent->_ws;
    _wp = Vector3(pp.x + ps.x * _lp.x, pp.y + ps.y * _lp.y, pp.z + ps.z * _lp.z);
    _ws = Vector3(_ls.x * ps.x, _ls.y * ps.y, _ls.z * ps.z);
  } else { _wp = _lp; _ws = _ls; }
  _wDirty = false; _wVer++;
}
Vector3 Transform::get_position() const { _updateWorld(); return _wp; }
Vector3 Transform::get_lossyScale() const { _updateWorld(); return _ws; }
void Transform::set_position(const Vector3& w) {
  Vector3 nl = w;
  if (_parent) { Vector3 pp = _parent->get_position(), ps = _parent->get_lossyScale(); nl = Vector3(ps.x ? (w.x - pp.x) / ps.x : 0, ps.y ? (w.y - pp.y) / ps.y : 0, ps.z ? (w.z - pp.z) / ps.z : 0); }
  if (nl.x == _lp.x && nl.y == _lp.y && nl.z == _lp.z) return;   // unchanged: keep the cached world positions below
  _lp = nl; _invalidate();
}
void Transform::_detach() { if (_parent) { auto& v = _parent->_children; v.erase(std::remove(v.begin(), v.end(), this), v.end()); bumpHier(_parent); _parent = nullptr; _invalidateForce(); invalidateActive(this); } }
void Transform::SetParent(const P<Transform>& p, bool stay) {
  for (Transform* t = p.get(); t; t = t->_parent) if (t == this) { cs::log("SetParent: refusing to parent %s to itself or a child", gameObject.get() ? gameObject->_name.utf8().c_str() : "?"); return; }
  Vector3 wp = get_position(); Vector3 ws = get_lossyScale();
  bool before = gameObject.get() ? goActive(gameObject.get()) : false;
  _detach();
  if (p.get()) { _parent = p.get(); _parent->_children.push_back(this); }
  if (stay) {
    set_position(wp);
    if (_parent) { Vector3 ps = _parent->get_lossyScale(); _ls = Vector3(ps.x ? ws.x / ps.x : 0, ps.y ? ws.y / ps.y : 0, ps.z ? ws.z / ps.z : 0); } else _ls = ws;
  }
  _invalidateForce(); invalidateActive(this); bumpHier(this);
  if (gameObject.get()) {
    if (_parent && _parent->gameObject.get()) gameObject->_scene = _parent->gameObject->_scene;
    bool after = goActive(gameObject.get()); if (before != after) onBecameActive(gameObject.get(), after);
  }
}
void Transform::set_parent(const P<Transform>& p) { SetParent(p, true); }
P<Transform> Transform::Find(const String& path) const {
  std::u16string s = path.u(); const Transform* cur = this;
  size_t start = 0;
  while (cur) {
    size_t slash = s.find(u'/', start);
    std::u16string part = s.substr(start, slash == std::u16string::npos ? std::u16string::npos : slash - start);
    const Transform* next = nullptr;
    for (Transform* c : cur->_children) if (c->gameObject.get() && c->gameObject->_name.u() == part) { next = c; break; }
    if (!next) return nullptr;
    cur = next;
    if (slash == std::u16string::npos) return P<Transform>(const_cast<Transform*>(cur));
    start = slash + 1;
  }
  return nullptr;
}

// ======================================================================= Find
static bool nameMatchesPath(GameObject* go, const std::u16string& path) {
  // "a/b/c": go named c, parent b, grandparent a. Leading '/' means a must be a root.
  bool absolute = !path.empty() && path[0] == u'/';
  std::u16string p = absolute ? path.substr(1) : path;
  std::vector<std::u16string> parts; size_t st = 0;
  for (;;) { size_t k = p.find(u'/', st); parts.push_back(p.substr(st, k == std::u16string::npos ? std::u16string::npos : k - st)); if (k == std::u16string::npos) break; st = k + 1; }
  Transform* t = go->transform.get();
  for (int i = (int)parts.size() - 1; i >= 0; i--) {
    if (!t || !t->gameObject.get() || t->gameObject->_name.u() != parts[i]) return false;
    t = t->_parent;
  }
  return !absolute || t == nullptr;
}
struct FindIndex { int gen = -1; std::unordered_map<std::u16string, std::vector<GameObject*>> byName, byTag; };
static FindIndex fidx;
static void indexAdd(GameObject* go) { if (fidx.gen != g.gen || go->_scene == -3) return; fidx.byName[go->_name.u()].push_back(go); fidx.byTag[go->_tag.u()].push_back(go); }
static void indexRemove(std::unordered_map<std::u16string, std::vector<GameObject*>>& m, const std::u16string& key, GameObject* go) {
  auto it = m.find(key); if (it == m.end()) return; auto& v = it->second; v.erase(std::remove(v.begin(), v.end(), go), v.end()); if (v.empty()) m.erase(it);
}
static void indexRename(GameObject* go, const String& oldName) { if (fidx.gen != g.gen) return; indexRemove(fidx.byName, oldName.u(), go); fidx.byName[go->_name.u()].push_back(go); }
static void indexRetag(GameObject* go, const String& oldTag) { if (fidx.gen != g.gen) return; indexRemove(fidx.byTag, oldTag.u(), go); fidx.byTag[go->_tag.u()].push_back(go); }
static void indexDrop(GameObject* go) { if (fidx.gen != g.gen) return; indexRemove(fidx.byName, go->_name.u(), go); indexRemove(fidx.byTag, go->_tag.u(), go); }
static FindIndex& findIndex() {
  if (fidx.gen != g.gen) {
    fidx.byName.clear(); fidx.byTag.clear();
    for (auto& go : g.objects) { if (go.isNull() || go->_scene == -3 || go->_destroyed) continue; fidx.byName[go->_name.u()].push_back(go.get()); fidx.byTag[go->_tag.u()].push_back(go.get()); }
    fidx.gen = g.gen;
  }
  return fidx;
}
P<GameObject> GameObject::Find(const String& name) {
  const std::u16string& n = name.u(); bool path = n.find(u'/') != std::u16string::npos;
  if (!path) {
    auto& m = findIndex().byName; auto it = m.find(n); if (it == m.end()) return nullptr;
    for (GameObject* go : it->second) if (!go->_destroyed && goActive(go)) return P<GameObject>(go);
    return nullptr;
  }
  for (auto& go : g.objects) {
    if (go.isNull() || go->_scene == -3) continue;
    if (path ? !nameMatchesPath(go.get(), n) : go->_name.u() != n) continue;
    if (goActive(go.get())) return go;
  }
  return nullptr;
}
P<GameObject> GameObject::FindGameObjectWithTag(const String& tag) {
  { auto& m = findIndex().byTag; auto it = m.find(tag.u()); if (it == m.end()) return nullptr; for (GameObject* go : it->second) if (!go->_destroyed && goActive(go)) return P<GameObject>(go); return nullptr; }
  for (auto& go : g.objects) if (!go.isNull() && go->_scene != -3 && go->_tag == tag && goActive(go.get())) return go;
  return nullptr;
}
Array<P<GameObject>> GameObject::FindGameObjectsWithTag(const String& tag) {
  Array<P<GameObject>> a = Array<P<GameObject>>::New(0);
  for (auto& go : g.objects) if (!go.isNull() && go->_scene != -3 && go->_tag == tag && goActive(go.get())) a.vec().push_back(go);
  return a;
}

// ======================================================================= destroy
static void destroyGameObjectNow(GameObject* go, bool sceneUnload);
static void destroyComponentNow(Component* c) {
  if (c->_destroyed) return;
  if (auto* mb = dynamic_cast<MonoBehaviour*>(c)) {
    disable(mb);
    if (mb->_awoken && mb->_cls && !g.viewer) call(mb, mb->_cls->OnDestroy, "OnDestroy");
    g.timers.erase(std::remove_if(g.timers.begin(), g.timers.end(), [&](const Timer& t) { return t.mb.get() == mb; }), g.timers.end());
  }
  if (auto* as = dynamic_cast<AudioSource*>(c)) as->Stop();
  regRemove(c);
  c->_destroyed = true;
}
static void destroyGameObjectNow(GameObject* go, bool sceneUnload) {
  if (go->_destroyed) return;
  P<GameObject> keep(go);
  auto kids = go->transform.get() ? go->transform->_children : std::vector<Transform*>();
  for (Transform* k : kids) if (k->gameObject.get()) destroyGameObjectNow(k->gameObject.get(), sceneUnload);
  auto comps = go->_comps;
  for (auto& c : comps) if (c.get()) destroyComponentNow(c.get());
  if (go->transform.get()) go->transform->_detach();
  go->_destroyed = true;
  if (g.hover.get() == go) g.hover = nullptr;
  if (g.pressed.get() == go) g.pressed = nullptr;
  indexDrop(go); g.camGen++; invalidateActive(go->transform.get());
  if (sceneUnload) {
    // break reference cycles so memory is returned
    for (auto& c : comps) if (auto* mb = compAs<MonoBehaviour>(c.get())) mb->_clearRefs();
    for (auto& c : comps) if (c.get()) { c->gameObject = nullptr; c->transform = nullptr; }
    go->_comps.clear(); go->transform = nullptr;
  } else g.zombies.push_back(P<GameObject>(go));
}
// Releases what Destroy() removed during play. Their scripts' references are cleared like a scene unload does, so the
// objects can be freed (until then they are kept, so code still holding them this scene sees them as Unity would).
static void releaseZombies() {
  auto zs = std::move(g.zombies); g.zombies.clear();
  auto zc = std::move(g.zombieComps); g.zombieComps.clear();
  for (auto& go : zs) {
    if (!go.get()) continue;
    auto comps = go->_comps;
    for (auto& c : comps) if (auto* mb = compAs<MonoBehaviour>(c.get())) mb->_clearRefs();
    for (auto& c : comps) if (c.get()) { c->gameObject = nullptr; c->transform = nullptr; }
    go->_comps.clear(); go->transform = nullptr;
  }
  for (auto& c : zc) if (c.get()) { if (auto* mb = compAs<MonoBehaviour>(c.get())) mb->_clearRefs(); c->gameObject = nullptr; c->transform = nullptr; }
}
void Object::Destroy(const P<Object>& o, float t) {
  if (o.isNull()) return;
  if (t > 0) { g.delayed.push_back({ o, Time::_time + t }); return; }
  o.get()->_pendingDestroy = true;
  if (auto* go = dynamic_cast<GameObject*>(o.get())) walkHierarchy(go->transform.get(), [](GameObject* x) { x->_pendingDestroy = true; for (auto& c : x->_comps) if (c.get()) c->_pendingDestroy = true; });
  g.destroyQueue.push_back(o);
}
static void flushDestroyed() {
  for (size_t i = 0; i < g.delayed.size();) { if (g.delayed[i].at <= Time::_time) { g.destroyQueue.push_back(g.delayed[i].o); g.delayed.erase(g.delayed.begin() + i); } else i++; }
  while (!g.destroyQueue.empty()) {
    auto q = std::move(g.destroyQueue); g.destroyQueue.clear();
    for (auto& o : q) {
      if (o.get() == nullptr || o.get()->_destroyed) continue;
      if (auto* go = dynamic_cast<GameObject*>(o.get())) destroyGameObjectNow(go, false);
      else if (auto* c = dynamic_cast<Component*>(o.get())) {
        destroyComponentNow(c); g.zombieComps.push_back(P<Component>(c));
        if (c->gameObject.get()) { auto& v = c->gameObject->_comps; v.erase(std::remove_if(v.begin(), v.end(), [&](const P<Component>& x) { return x.get() == c; }), v.end()); }
      } else o.get()->_destroyed = true;
    }
  }
  size_t before = g.objects.size();
  g.objects.erase(std::remove_if(g.objects.begin(), g.objects.end(), [](const P<GameObject>& go) { return go.get() == nullptr || go.get()->_destroyed; }), g.objects.end());
  g.behaviours.erase(std::remove_if(g.behaviours.begin(), g.behaviours.end(), [](const P<MonoBehaviour>& m) { return m.get() == nullptr || m.get()->_destroyed; }), g.behaviours.end());
}
void Object::DontDestroyOnLoad(const P<Object>& o) {
  if (o.isNull()) return;
  GameObject* go = dynamic_cast<GameObject*>(o.get());
  if (!go) if (auto* c = dynamic_cast<Component*>(o.get())) go = c->gameObject.get();
  if (!go) return;
  Transform* root = go->transform.get(); while (root && root->_parent) root = root->_parent;
  walkHierarchy(root, [](GameObject* x) { x->_scene = -2; });
}

// ======================================================================= assets
static P<Texture2D> getTexture(int ki) {
  if (ki < 0 || ki >= (int)g.texObjs.size()) return nullptr;
  if (g.texObjs[ki].isNull()) {
    const JVal& t = g.textures[ki]; P<Texture2D> x(new Texture2D());
    x->_texIndex = ki; x->_w = t["w"].i(); x->_h = t["h"].i(); x->_name = String(t["n"].str().c_str()); x->_filter = (FilterMode)t["fm"].i();
    g.texObjs[ki] = x;
  }
  return g.texObjs[ki];
}
static P<Sprite> getSprite(int ki) {
  if (ki < 0 || ki >= (int)g.spriteObjs.size()) return nullptr;
  if (g.spriteObjs[ki].isNull()) {
    const JVal& s = g.sprites[ki]; P<Sprite> x(new Sprite());
    x->_index = ki; x->_name = String(s["n"].str().c_str()); x->_tex = getTexture(s["t"].i());
    x->_rect = Rect(s["r"][0].f(), s["r"][1].f(), s["r"][2].f(), s["r"][3].f());
    x->_pivotN = Vector2(s["p"][0].f(), s["p"][1].f()); x->_ppu = s["u"].f(100);
    g.spriteObjs[ki] = x;
  }
  return g.spriteObjs[ki];
}
static P<AudioClip> getAudio(int ki) {
  if (ki < 0 || ki >= (int)g.audioObjs.size()) return nullptr;
  if (g.audioObjs[ki].isNull()) { const JVal& a = g.audio[ki]; P<AudioClip> x(new AudioClip()); x->_index = ki; x->_name = String(a["n"].str().c_str()); x->_length = a["len"].f(); x->_channels = a["ch"].i(); x->_freq = a["hz"].i(); g.audioObjs[ki] = x; }
  return g.audioObjs[ki];
}
static P<TextAsset> getText(int ki) {
  if (ki < 0 || ki >= (int)g.textObjs.size()) return nullptr;
  if (g.textObjs[ki].isNull()) {
    P<TextAsset> x(new TextAsset()); x->_index = ki; x->_name = String(g.texts[ki]["n"].str().c_str());
    std::string s = readFile(g.data + "/text/" + std::to_string(ki) + ".txt");
    if (s.size() >= 3 && (uint8_t)s[0] == 0xEF && (uint8_t)s[1] == 0xBB && (uint8_t)s[2] == 0xBF) s = s.substr(3);
    x->_text = String::FromUtf8(s.data(), s.size()); g.textObjs[ki] = x;
  }
  return g.textObjs[ki];
}
static P<AnimationClip> getClip(int ki) {
  if (ki < 0 || ki >= (int)g.clipObjs.size()) return nullptr;
  if (g.clipObjs[ki].isNull()) { P<AnimationClip> x(new AnimationClip()); x->_index = ki; x->_name = String(g.anims[ki]["n"].str().c_str()); g.clipObjs[ki] = x; }
  return g.clipObjs[ki];
}
float AnimationClip::get_length() const { return g.anims[_index]["len"].f(); }
static P<RuntimeAnimatorController> getCtrl(int ki) {
  if (ki < 0 || ki >= (int)g.ctrlObjs.size()) return nullptr;
  if (g.ctrlObjs[ki].isNull()) { P<RuntimeAnimatorController> x(new RuntimeAnimatorController()); x->_index = ki; x->_name = String(g.ctrls[ki]["n"].str().c_str()); g.ctrlObjs[ki] = x; }
  return g.ctrlObjs[ki];
}
static P<GameObject> getPrefab(int ki);
// The project's materials: only their names say how they draw (see Material::_blend).
static P<Material> getMaterial(int ki) {
  static std::vector<P<Material>> mats;
  const JVal& ids = g.assetIndex["mat"];
  if (ki < 0 || ki >= (int)ids.size()) return nullptr;
  if ((int)mats.size() < (int)ids.size()) mats.resize(ids.size());
  if (mats[ki].isNull()) {
    std::string n = g.assetIndex["all"][(size_t)ids[ki].i()][2].str();
    P<Material> m(new Material(P<Shader>())); m->_name = String(n.c_str());
    m->_blend = n.find("Multiply") != std::string::npos ? 1 : n.find("Overlay") != std::string::npos ? 2 : 0;
    mats[ki] = m;
  }
  return mats[ki];
}

static P<Object> assetByKind(const std::string& kind, int ki) {
  if (kind == "sprite") return getSprite(ki);
  if (kind == "tex") return getTexture(ki);
  if (kind == "audio") return getAudio(ki);
  if (kind == "text") return getText(ki);
  if (kind == "prefab") return getPrefab(ki);
  if (kind == "anim") return getClip(ki);
  if (kind == "ctrl") return getCtrl(ki);
  if (kind == "mat") return getMaterial(ki);
  return nullptr;
}

// ======================================================================= building objects from scene/prefab JSON
struct Builder : RefResolver {
  std::map<long long, P<Object>> byId;
  P<Object> local(long long id) override { auto it = byId.find(id); return it == byId.end() ? nullptr : it->second; }
  P<Object> asset(int gi, long long fileID) override;
};

static std::vector<P<GameObject>> buildObjects(const JVal& objs, int sceneSlot, Builder& b, std::vector<MonoBehaviour*>& newScripts);

static const JVal& prefabJson(int ki) {
  static std::map<int, JVal> cache;   // prefabs are small and reused (particles): parse each once
  auto it = cache.find(ki); if (it != cache.end()) return it->second;
  std::string s = readFile(g.data + "/prefabs/" + std::to_string(ki) + ".json");
  JVal& pj = cache[ki]; JParser::parse(s.data(), s.size(), pj); return pj;
}
static P<GameObject> instantiatePrefab(int ki, int sceneSlot, std::vector<MonoBehaviour*>& newScripts) {
  const JVal& pj = prefabJson(ki);
  Builder b; auto roots = buildObjects(pj["objs"], sceneSlot, b, newScripts);
  P<Object> r = b.local((long long)pj["root"].num());
  return r.as<GameObject>();
}
static P<GameObject> getPrefab(int ki) {
  if (ki < 0 || ki >= (int)g.prefabObjs.size()) return nullptr;
  if (g.prefabObjs[ki].isNull()) {
    // Prefab "asset": an inactive template kept outside the scene, never awoken
    std::vector<MonoBehaviour*> dummy;
    bool v = g.viewer; g.viewer = true;
    P<GameObject> t = instantiatePrefab(ki, -3, dummy);
    g.viewer = v;
    if (t.get()) { t->_scene = -3; walkHierarchy(t->transform.get(), [](GameObject* x) { x->_scene = -3; }); t->set_name(String(g.prefabs[ki]["n"].str().c_str())); t->_prefabIndex = ki; }
    g.prefabObjs[ki] = t;
  }
  return g.prefabObjs[ki];
}
P<Object> Builder::asset(int gi, long long fileID) {
  const JVal& e = g.assetIndex["all"][gi];
  std::string kind = e[0].str(); int ki = e[1].i();
  if (kind == "prefab" && fileID) {
    P<GameObject> root = getPrefab(ki);
    if (root.isNull()) return nullptr;
    // reference to an object inside the prefab: look it up by original file ID
    P<Object> found;
    walkHierarchy(root->transform.get(), [&](GameObject* x) {
      if (found.get()) return;
      if (x->_srcId == fileID) { found = P<Object>(x); return; }
      for (auto& c : x->_comps) if (c.get() && c->_srcId == fileID) { found = P<Object>(c.get()); return; }
    });
    return found.get() ? found : P<Object>(root);
  }
  return assetByKind(kind, ki);
}

static float jf(const JVal& a, int i) { return a[i].f(); }

static std::vector<P<GameObject>> buildObjects(const JVal& objs, int sceneSlot, Builder& b, std::vector<MonoBehaviour*>& newScripts) {
  int prevScene = g.activeScene; g.activeScene = sceneSlot;
  std::vector<std::pair<const JVal*, P<GameObject>>> made;
  // pass 1: objects and components
  for (size_t i = 0; i < objs.size(); i++) {
    const JVal& o = objs[i];
    P<GameObject> go(new GameObject(String(o["n"].str().c_str())));
    go->_srcId = (long long)o["id"].num();
    go->_active = o["a"].i() != 0; go->_layer = o["l"].i(); { String old = go->_tag; go->_tag = String(o["tag"].str().c_str()); indexRetag(go.get(), old); }
    go->_scene = sceneSlot;
    Transform* t = go->transform.get();
    t->_lp = Vector3(jf(o["p"], 0), jf(o["p"], 1), jf(o["p"], 2));
    t->_ls = Vector3(jf(o["s"], 0), jf(o["s"], 1), jf(o["s"], 2));
    b.byId[go->_srcId] = go;
    const JVal& comps = o["c"];
    for (size_t k = 0; k < comps.size(); k++) {
      const JVal& c = comps[k]; const std::string& kind = c["k"].str();
      Component* comp = nullptr;
      if (kind == "sr") comp = new SpriteRenderer();
      else if (kind == "box") comp = new BoxCollider2D();
      else if (kind == "circle") comp = new CircleCollider2D();
      else if (kind == "poly") comp = new PolygonCollider2D();
      else if (kind == "animator") comp = new Animator();
      else if (kind == "audio") comp = new AudioSource();
      else if (kind == "camera") comp = new Camera();
      else if (kind == "listener") comp = new AudioListener();
      else if (kind == "reverb") comp = new AudioReverbFilter();
      else if (kind == "mask") comp = new SpriteMask();
      else if (kind == "guilayer") comp = new GUILayer();
      else if (kind == "flare") comp = new FlareLayer();
      else if (kind == "mb") {
        const ClassInfo* ci = g.viewer ? nullptr : findClass(c["cls"].str().c_str());
        MonoBehaviour* mb = ci && ci->create ? ci->create() : new MonoBehaviour();
        mb->_cls = ci;
        comp = mb;
      } else continue;
      comp->_srcId = (long long)c["id"].num();
      comp->gameObject = go; comp->transform = go->transform; comp->_name = go->_name;
      if (auto* bh = dynamic_cast<Behaviour*>(comp)) bh->_enabled = c["en"].i(1) != 0;
      if (auto* r = dynamic_cast<Renderer*>(comp)) r->_enabled = c["en"].i(1) != 0;
      go->_comps.push_back(P<Component>(comp)); regAdd(comp);
      b.byId[comp->_srcId] = P<Object>(comp);
    }
    made.push_back({ &o, go });
  }
  // hierarchy
  for (auto& m : made) {
    const JVal& ch = (*m.first)["ch"];
    for (size_t k = 0; k < ch.size(); k++) {
      P<GameObject> kid = b.local((long long)ch[k].num()).as<GameObject>();
      if (kid.get()) { kid->transform->_parent = m.second->transform.get(); m.second->transform->_children.push_back(kid->transform.get()); }
    }
  }
  for (auto& m : made) { m.second->transform->_wDirty = true; m.second->_actStamp = -1; }
  // pass 2: component data (needs every object to exist for references)
  for (auto& m : made) {
    const JVal& comps = (*m.first)["c"]; GameObject* go = m.second.get();
    size_t ci = 1; // component 0 is the Transform
    for (size_t k = 0; k < comps.size(); k++) {
      const JVal& c = comps[k];
      P<Object> obj = b.local((long long)c["id"].num()); if (obj.isNull()) continue;
      const std::string& kind = c["k"].str();
      if (kind == "sr") {
        auto* s = static_cast<SpriteRenderer*>(obj.get());
        P<Sprite> sp; FieldReader::read(c["sp"], sp, &b); s->_sprite = sp;
        P<Material> mat; FieldReader::read(c["mat"], mat, &b); s->_material = mat;
        s->_color = Color(jf(c["col"], 0), jf(c["col"], 1), jf(c["col"], 2), jf(c["col"], 3));
        s->_flipX = c["fx"].i() != 0; s->_flipY = c["fy"].i() != 0; s->_sortingLayer = c["sl"].i(); s->_sortingOrder = c["so"].i();
        s->_mask = (SpriteMaskInteraction)c["mi"].i();
      } else if (kind == "box") {
        auto* x = static_cast<BoxCollider2D*>(obj.get()); x->_trigger = c["tr"].i() != 0; x->_offset = Vector2(jf(c["off"], 0), jf(c["off"], 1)); x->_size = Vector2(jf(c["sz"], 0), jf(c["sz"], 1));
      } else if (kind == "circle") {
        auto* x = static_cast<CircleCollider2D*>(obj.get()); x->_trigger = c["tr"].i() != 0; x->_offset = Vector2(jf(c["off"], 0), jf(c["off"], 1)); x->_radius = c["rad"].f();
      } else if (kind == "poly") {
        auto* x = static_cast<PolygonCollider2D*>(obj.get()); x->_trigger = c["tr"].i() != 0; x->_offset = Vector2(jf(c["off"], 0), jf(c["off"], 1));
        const JVal& ps = c["paths"];
        for (size_t p = 0; p < ps.size(); p++) { std::vector<Vector2> pts; for (size_t q = 0; q + 1 < ps[p].size(); q += 2) pts.push_back(Vector2(ps[p][q].f(), ps[p][q + 1].f())); x->_paths.push_back(pts); }
      } else if (kind == "animator") {
        static_cast<Animator*>(obj.get())->_ctrl = c["ctrl"].i(-1);
      } else if (kind == "audio") {
        auto* a = static_cast<AudioSource*>(obj.get());
        a->_clip = getAudio(c["clip"].i(-1)); a->_volume = c["vol"].f(1); a->_pitch = c["pitch"].f(1); a->_loop = c["loop"].i() != 0;
        a->_playOnAwake = c["poa"].i() != 0; a->_mute = c["mute"].i() != 0; a->_pan = c["pan"].f();
      } else if (kind == "camera") {
        auto* cam = static_cast<Camera*>(obj.get());
        cam->_ortho = c["ortho"].i() != 0; cam->_size = c["os"].f(); cam->_depth = c["depth"].f(); cam->_mask = c["mask"].i(-1);
        cam->_clear = (CameraClearFlags)c["clear"].i(1);
        cam->_bg = Color(jf(c["bg"], 0), jf(c["bg"], 1), jf(c["bg"], 2), jf(c["bg"], 3));
        cam->_rect = Rect(jf(c["rect"], 0), jf(c["rect"], 1), jf(c["rect"], 2), jf(c["rect"], 3));
      } else if (kind == "reverb") {
        static_cast<AudioReverbFilter*>(obj.get())->_preset = (AudioReverbPreset)c["preset"].i();
      } else if (kind == "mask") {
        auto* m2 = static_cast<SpriteMask*>(obj.get()); P<Sprite> sp; FieldReader::read(c["sp"], sp, &b); m2->_sprite = sp; m2->_cutoff = c["cut"].f(0.2f);
      } else if (kind == "mb") {
        auto* mb = static_cast<MonoBehaviour*>(obj.get());
        if (mb->_cls) { FieldReader fr(&c["f"], &b); guarded(mb, "load fields", [&] { mb->_load(fr); }); }
        newScripts.push_back(mb);
        if (sceneSlot != -3) { g.behaviours.push_back(P<MonoBehaviour>(mb)); g.behavioursDirty = true; }
      }
      (void)go; (void)ci;
    }
  }
  g.activeScene = prevScene;
  std::vector<P<GameObject>> roots;
  for (auto& m : made) if (!m.second->transform->_parent) roots.push_back(m.second);
  return roots;
}

static void sortBehaviours() {
  if (!g.behavioursDirty) return;
  std::stable_sort(g.behaviours.begin(), g.behaviours.end(), [](const P<MonoBehaviour>& a, const P<MonoBehaviour>& b) {
    int ea = a.get() && a.get()->_cls ? a.get()->_cls->execOrder : 0, eb = b.get() && b.get()->_cls ? b.get()->_cls->execOrder : 0; return ea < eb; });
  g.behavioursDirty = false;
}

static void startObjects(std::vector<MonoBehaviour*>& scripts) {
  std::stable_sort(scripts.begin(), scripts.end(), [](MonoBehaviour* a, MonoBehaviour* b) { return (a->_cls ? a->_cls->execOrder : 0) < (b->_cls ? b->_cls->execOrder : 0); });
  for (MonoBehaviour* mb : scripts) if (mb->gameObject.get() && goActive(mb->gameObject.get())) awakeAndEnable(mb);
}

static void playOnAwakeSources(const std::vector<P<GameObject>>& roots) {
  for (auto& r : roots) walkHierarchy(r->transform.get(), [](GameObject* go) {
    if (!goActive(go)) return;
    for (auto& c : go->_comps) if (auto* a = dynamic_cast<AudioSource*>(c.get())) if (a->_playOnAwake && a->_enabled) a->Play();
  });
}

void engine::loadSceneNow(int index) {
  if (index < 0 || index >= (int)g.manifest["scenes"].size()) { cs::log("LoadScene: bad index %d", index); return; }
  // unload current scene objects (everything not marked DontDestroyOnLoad)
  auto objs = g.objects;
  for (auto& go : objs) if (go.get() && !go->_destroyed && go->_scene >= 0 && (!go->transform.get() || !go->transform->_parent)) destroyGameObjectNow(go.get(), true);
  releaseZombies();
  g.objects.erase(std::remove_if(g.objects.begin(), g.objects.end(), [](const P<GameObject>& go) { return !go.get() || go->_destroyed; }), g.objects.end());
  g.behaviours.erase(std::remove_if(g.behaviours.begin(), g.behaviours.end(), [](const P<MonoBehaviour>& m) { return !m.get() || m->_destroyed; }), g.behaviours.end());
  g.timers.erase(std::remove_if(g.timers.begin(), g.timers.end(), [](const Timer& t) { return t.mb.isNull(); }), g.timers.end());
  g.hover = nullptr; g.pressed = nullptr; g.gen++;
  std::string s = readFile(g.data + "/scenes/" + std::to_string(index) + ".json");
  JVal sj; JParser::parse(s.data(), s.size(), sj);
  g.activeScene = index;
  Builder b; std::vector<MonoBehaviour*> scripts;
  auto roots = buildObjects(sj["objs"], index, b, scripts);
  g.activeScene = index;
  g_sceneLoads++;
  cs::log("scene %d %s: %d objects, %d scripts", index, sj["name"].str().c_str(), (int)sj["objs"].size(), (int)scripts.size());
  startObjects(scripts);
  playOnAwakeSources(roots);
  if (!g.viewer) {
    sortBehaviours();
    auto all = g.behaviours;
    for (auto& mb : all) if (mb.get() && !mb->_destroyed && mb->_cls && mb->_cls->OnLevelWasLoaded && mb->_enabled && mb->gameObject.get() && goActive(mb->gameObject.get()))
      guarded(mb.get(), "OnLevelWasLoaded", [&] { mb->_cls->OnLevelWasLoaded(mb.get(), index); });
  }
}

// ======================================================================= Instantiate
Object::Object(const Object& o) : Obj(), _name(o._name), _srcId(o._srcId) { _id = g.nextId++;
#ifdef DE_LEAKCHECK
  liveSet().insert(this);
#endif
}

static Component* cloneBuiltin(Component* sc) {
  if (auto* x = dynamic_cast<SpriteRenderer*>(sc)) return new SpriteRenderer(*x);
  if (auto* x = dynamic_cast<SpriteMask*>(sc)) return new SpriteMask(*x);
  if (auto* x = dynamic_cast<BoxCollider2D*>(sc)) return new BoxCollider2D(*x);
  if (auto* x = dynamic_cast<CircleCollider2D*>(sc)) return new CircleCollider2D(*x);
  if (auto* x = dynamic_cast<PolygonCollider2D*>(sc)) return new PolygonCollider2D(*x);
  if (auto* x = dynamic_cast<Animator*>(sc)) { auto* a = new Animator(*x); a->_inited = false; a->_state = -1; a->_time = 0; a->_lastEventFrame = -1; a->_fromClip = -1; return a; }
  if (auto* x = dynamic_cast<AudioSource*>(sc)) { auto* a = new AudioSource(*x); a->_voice = -1; return a; }
  if (auto* x = dynamic_cast<Camera*>(sc)) return new Camera(*x);
  if (auto* x = dynamic_cast<AudioListener*>(sc)) return new AudioListener(*x);
  if (auto* x = dynamic_cast<AudioReverbFilter*>(sc)) return new AudioReverbFilter(*x);
  if (auto* x = dynamic_cast<GUILayer*>(sc)) return new GUILayer(*x);
  if (auto* x = dynamic_cast<FlareLayer*>(sc)) return new FlareLayer(*x);
  if (auto* x = dynamic_cast<SortingGroup*>(sc)) return new SortingGroup(*x);
  if (auto* x = dynamic_cast<Rigidbody2D*>(sc)) return new Rigidbody2D(*x);
  return nullptr;
}
struct CloneRefs : RefResolver {
  std::vector<P<Object>> refs;
  P<Object> local(long long id) override { return id >= 0 && id < (long long)refs.size() ? refs[(size_t)id] : nullptr; }
  P<Object> asset(int, long long) override { return nullptr; }
};
// Unity's Instantiate: copy the hierarchy, copy each script's serialized fields (private fields get fresh
// defaults), and point references to objects inside the copied hierarchy at their copies.
static P<GameObject> cloneLive(GameObject* src, std::map<Obj*, Obj*>& map, std::vector<MonoBehaviour*>& scripts) {
  std::vector<std::pair<GameObject*, GameObject*>> gos;
  std::function<GameObject*(GameObject*, Transform*)> mk = [&](GameObject* s, Transform* parent) -> GameObject* {
    GameObject* d = new GameObject(s->_name);
    d->_active = s->_active; d->_layer = s->_layer; { String old = d->_tag; d->_tag = s->_tag; indexRetag(d, old); } d->_scene = g.activeScene; d->_srcId = s->_srcId;
    d->transform->_lp = s->transform->_lp; d->transform->_ls = s->transform->_ls;
    if (parent) { d->transform->_parent = parent; parent->_children.push_back(d->transform.get()); }
    map[s] = d; map[s->transform.get()] = d->transform.get();
    gos.push_back({ s, d });
    auto kids = s->transform->_children;
    for (Transform* k : kids) if (k->gameObject.get() && !k->gameObject->_destroyed) mk(k->gameObject.get(), d->transform.get());
    return d;
  };
  GameObject* root = mk(src, nullptr);
  g.camGen++; invalidateActive(root->transform.get());
  std::vector<std::pair<MonoBehaviour*, MonoBehaviour*>> mbs;
  for (auto& pr : gos) {
    GameObject* s = pr.first; GameObject* d = pr.second;
    auto comps = s->_comps;
    for (auto& c : comps) {
      Component* sc = c.get(); if (!sc || sc->_destroyed || dynamic_cast<Transform*>(sc)) continue;
      Component* dc = nullptr;
      if (auto* mb = dynamic_cast<MonoBehaviour*>(sc)) {
        if (!mb->_cls || !mb->_cls->create) continue;
        MonoBehaviour* n = mb->_cls->create(); n->_cls = mb->_cls; n->_enabled = mb->_enabled;
        dc = n; mbs.push_back({ mb, n });
      } else dc = cloneBuiltin(sc);
      if (!dc) continue;
      dc->gameObject = P<GameObject>(d); dc->transform = d->transform; dc->_name = d->_name; dc->_srcId = sc->_srcId;
      d->_comps.push_back(P<Component>(dc)); regAdd(dc); map[sc] = dc;
    }
  }
  for (auto& pr : mbs) {
    MonoBehaviour* s = pr.first; MonoBehaviour* d = pr.second;
    CloneRefs res; JsonWriter w;
    w.refWriter = [&](JsonWriter& jw, Obj* o) {
      auto it = map.find(o); Obj* t = it != map.end() ? it->second : o;
      jw.out += "{\"r\":" + std::to_string(res.refs.size()) + "}";
      res.refs.push_back(P<Object>(dynamic_cast<Object*>(t)));
    };
    w.out = "{";
    guarded(s, "Instantiate (copy fields)", [&] { s->_saveSerialized(w); });
    w.out += "}";
    JVal j; JParser::parse(w.out.data(), w.out.size(), j);
    FieldReader fr(&j, &res);
    guarded(d, "Instantiate (load fields)", [&] { d->_load(fr); });
    g.behaviours.push_back(P<MonoBehaviour>(d)); g.behavioursDirty = true;
    scripts.push_back(d);
  }
  return P<GameObject>(root);
}
P<Object> Object::Instantiate(const P<Object>& original) {
  if (original.isNull()) throw NullReferenceException();
  GameObject* src = dynamic_cast<GameObject*>(original.get());
  if (!src) if (auto* c = dynamic_cast<Component*>(original.get())) src = c->gameObject.get();
  if (!src) { cs::log("Instantiate of non-GameObject %s not supported", original->_name.utf8().c_str()); return nullptr; }
  std::vector<MonoBehaviour*> scripts; std::map<Obj*, Obj*> map;
  P<GameObject> copy;
  if (src->_prefabIndex >= 0) copy = instantiatePrefab(src->_prefabIndex, g.activeScene, scripts);
  else copy = cloneLive(src, map, scripts);
  if (copy.isNull()) return nullptr;
  copy->set_name(src->_name + S("(Clone)"));
  copy->transform->_lp = src->transform->get_position(); copy->transform->_ls = src->transform->get_lossyScale();
  copy->transform->_invalidateForce();
  copy->_active = src->_active; invalidateActive(copy->transform.get());
  walkHierarchy(copy->transform.get(), [](GameObject* x) { x->_scene = g.activeScene; });
  startObjects(scripts);
  std::vector<P<GameObject>> roots{ copy }; playOnAwakeSources(roots);
  if (auto* c = dynamic_cast<Component*>(original.get())) {
    auto it = map.find(c); if (it != map.end()) return P<Object>(dynamic_cast<Object*>(it->second));
    int idx = 0; for (auto& k : src->_comps) { if (k.get() == c) break; idx++; }
    if (idx < (int)copy->_comps.size()) return P<Object>(copy->_comps[idx].get());
  }
  return copy;
}
P<GameObject> Object::Instantiate(const P<GameObject>& original, const Vector3& pos, const Quaternion&) {
  P<GameObject> go = Instantiate(P<Object>(original)).as<GameObject>();
  if (go.get()) go->transform->set_position(pos);
  return go;
}

// ======================================================================= Invoke
void MonoBehaviour::Invoke(const String& m, float t) { g.timers.push_back({ P<MonoBehaviour>(this), m.utf8(), Time::_time + (t > 0 ? t : 0), 0, false }); }
void MonoBehaviour::InvokeRepeating(const String& m, float t, float r) { g.timers.push_back({ P<MonoBehaviour>(this), m.utf8(), Time::_time + (t > 0 ? t : 0), r, true }); }
void MonoBehaviour::CancelInvoke() { for (auto& t : g.timers) if (t.mb.get() == this) t.dead = true; }
void MonoBehaviour::CancelInvoke(const String& m) { std::string n = m.utf8(); for (auto& t : g.timers) if (t.mb.get() == this && t.name == n) t.dead = true; }
bool MonoBehaviour::IsInvoking(const String& m) const { std::string n = m.utf8(); for (auto& t : g.timers) if (t.mb.get() == this && t.name == n && !t.dead) return true; return false; }
void MonoBehaviour::print(const String& s) { cs::log("%s", s.utf8().c_str()); }
void MonoBehaviour::print(const P<Object>& o) { cs::log("%s", o.isNull() ? "Null" : o->ToString().utf8().c_str()); }

static void runTimers() {
  // fire timers in due order; new timers added during callbacks run next frame at the earliest
  size_t n = g.timers.size();
  for (size_t i = 0; i < n && i < g.timers.size(); i++) {
    Timer t = g.timers[i];
    if (t.dead || t.at > Time::_time) continue;
    MonoBehaviour* mb = t.mb.get();
    if (!mb || mb->_destroyed) { g.timers[i].dead = true; continue; }
    if (t.rep) g.timers[i].at += t.repeat > 0 ? t.repeat : 0.0001f; else g.timers[i].dead = true;
    if (mb->_cls && mb->_cls->invoke) {
      EventArg arg;
      double t0 = profTiming ? nowMs() : 0;
      guarded(mb, t.name.c_str(), [&] { if (!mb->_cls->invoke(mb, t.name.c_str(), arg)) cs::log("Invoke: %s has no method %s", mb->_cls->name, t.name.c_str()); });
      if (profTiming) noteCall(nowMs() - t0, mb->_cls, "Invoke", t.name.c_str());
    }
  }
  g.timers.erase(std::remove_if(g.timers.begin(), g.timers.end(), [](const Timer& t) { return t.dead; }), g.timers.end());
}

// ======================================================================= physics queries (static 2D colliders, no rotation)
static Vector2 colWorldOffset(const Collider2D* c, Vector2& scale) {
  Vector3 p = c->transform->get_position(); Vector3 s = c->transform->get_lossyScale(); scale = Vector2(s.x, s.y);
  return Vector2(p.x + c->_offset.x * s.x, p.y + c->_offset.y * s.y);
}
bool BoxCollider2D::_contains(const Vector2& p) const {
  Vector2 sc; Vector2 c = colWorldOffset(this, sc);
  float hw = std::fabs(_size.x * sc.x) * 0.5f, hh = std::fabs(_size.y * sc.y) * 0.5f;
  return p.x >= c.x - hw && p.x <= c.x + hw && p.y >= c.y - hh && p.y <= c.y + hh;
}
void BoxCollider2D::_localBounds(Vector2& mn, Vector2& mx) const { mn = _offset - _size * 0.5f; mx = _offset + _size * 0.5f; }
bool CircleCollider2D::_contains(const Vector2& p) const {
  Vector2 sc; Vector2 c = colWorldOffset(this, sc); float r = _radius * std::max(std::fabs(sc.x), std::fabs(sc.y));
  float dx = p.x - c.x, dy = p.y - c.y; return dx * dx + dy * dy <= r * r;
}
void CircleCollider2D::_localBounds(Vector2& mn, Vector2& mx) const { mn = _offset - Vector2(_radius, _radius); mx = _offset + Vector2(_radius, _radius); }
bool PolygonCollider2D::_contains(const Vector2& p) const {
  Vector3 tp = transform->get_position(); Vector3 s = transform->get_lossyScale();
  // to local space
  float lx = s.x ? (p.x - tp.x) / s.x - _offset.x : 0, ly = s.y ? (p.y - tp.y) / s.y - _offset.y : 0;
  bool inside = false;
  for (auto& path : _paths) {
    size_t n = path.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
      const Vector2 &a = path[i], &b = path[j];
      if (((a.y > ly) != (b.y > ly)) && (lx < (b.x - a.x) * (ly - a.y) / (b.y - a.y) + a.x)) inside = !inside;
    }
  }
  return inside;
}
void PolygonCollider2D::_localBounds(Vector2& mn, Vector2& mx) const {
  if (!_bValid) {
    _bMin = Vector2(1e9f, 1e9f); _bMax = Vector2(-1e9f, -1e9f);
    for (auto& p : _paths) for (auto& v : p) { _bMin.x = std::min(_bMin.x, v.x); _bMin.y = std::min(_bMin.y, v.y); _bMax.x = std::max(_bMax.x, v.x); _bMax.y = std::max(_bMax.y, v.y); }
    if (_bMin.x > _bMax.x) _bMin = _bMax = Vector2(0, 0);
    _bValid = true;
  }
  mn = _bMin + _offset; mx = _bMax + _offset;
}
Array<Vector2> PolygonCollider2D::GetPath(int i) const { if (i < 0 || i >= (int)_paths.size()) throw ArgumentOutOfRangeException(); return Array<Vector2>::FromVector(_paths[i]); }
void PolygonCollider2D::SetPath(int i, const Array<Vector2>& pts) { if (i < 0) throw ArgumentOutOfRangeException(); _bValid = false; if (i >= (int)_paths.size()) _paths.resize(i + 1); Array<Vector2> a = pts; _paths[i].assign(a.vec().begin(), a.vec().end()); }
void Collider2D::_worldBox(float& x0, float& y0, float& x1, float& y1) const {
  Vector2 mn, mx; _localBounds(mn, mx); Vector3 p = transform->get_position(), s = transform->get_lossyScale();
  x0 = p.x + mn.x * s.x; x1 = p.x + mx.x * s.x; y0 = p.y + mn.y * s.y; y1 = p.y + mx.y * s.y;
  if (x0 > x1) std::swap(x0, x1); if (y0 > y1) std::swap(y0, y1);
}
void CircleCollider2D::_worldBox(float& x0, float& y0, float& x1, float& y1) const {
  Vector2 sc; Vector2 c = colWorldOffset(this, sc); float r = _radius * std::max(std::fabs(sc.x), std::fabs(sc.y));
  x0 = c.x - r; x1 = c.x + r; y0 = c.y - r; y1 = c.y + r;
}
bool Collider2D::_segment(const Vector2& a, const Vector2& b, float& t) const {
  { float x0, y0, x1, y1; _worldBox(x0, y0, x1, y1); const float e = 1e-4f;   // skip colliders nowhere near the segment
    if (std::max(a.x, b.x) < x0 - e || std::min(a.x, b.x) > x1 + e || std::max(a.y, b.y) < y0 - e || std::min(a.y, b.y) > y1 + e) return false; }
  // sample along the segment (colliders here are hotspots; queries are nearly always points)
  float len = Vector2::Distance(a, b); int steps = len <= 0 ? 0 : std::min(256, (int)(len * 432) + 1);
  for (int i = 0; i <= steps; i++) { float f = steps ? (float)i / steps : 0; if (_contains(a + (b - a) * f)) { t = f; return true; } }
  return false;
}
Bounds Collider2D::get_bounds() const {
  Vector2 mn, mx; _localBounds(mn, mx); Vector3 p = transform->get_position(), s = transform->get_lossyScale();
  Vector2 a(p.x + mn.x * s.x, p.y + mn.y * s.y), b(p.x + mx.x * s.x, p.y + mx.y * s.y);
  Bounds bd; bd.center = Vector3((a.x + b.x) / 2, (a.y + b.y) / 2, p.z); bd.size = Vector3(std::fabs(b.x - a.x), std::fabs(b.y - a.y), 0); return bd;
}

struct Hit { Collider2D* c; float frac; float z; int order; };
static std::vector<Hit> queryColliders(const Vector2& a, const Vector2& b, int mask) {
  std::vector<Hit> hits;
  for (Component* c : reg(CK_COLLIDER)) {
    GameObject* go = liveOwner(c); if (!go || !(mask & (1 << go->_layer))) continue;
    auto* col = static_cast<Collider2D*>(c);
    if (!col->_enabled || !goActive(go)) continue;
    float f;
    if (col->_segment(a, b, f)) hits.push_back({ col, f, go->transform->get_position().z, (int)go->_serial });
  }
  std::stable_sort(hits.begin(), hits.end(), [](const Hit& x, const Hit& y) { if (x.frac != y.frac) return x.frac < y.frac; return x.z < y.z; });
  return hits;
}
RaycastHit2D Physics2D::Linecast(const Vector2& a, const Vector2& b, int mask) {
  auto h = queryColliders(a, b, mask); RaycastHit2D r;
  if (!h.empty()) { r._collider = P<Collider2D>(h[0].c); r.fraction = h[0].frac; r.point = a + (b - a) * h[0].frac; r.distance = Vector2::Distance(a, b) * h[0].frac; }
  return r;
}
Array<RaycastHit2D> Physics2D::LinecastAll(const Vector2& a, const Vector2& b, int mask) {
  auto h = queryColliders(a, b, mask); Array<RaycastHit2D> out = Array<RaycastHit2D>::New((int)h.size());
  for (size_t i = 0; i < h.size(); i++) { out[(int)i]._collider = P<Collider2D>(h[i].c); out[(int)i].fraction = h[i].frac; out[(int)i].point = a + (b - a) * h[i].frac; }
  return out;
}

// ======================================================================= cameras
static std::vector<Camera*> activeCameras() {
  std::vector<Camera*> cams;
  for (Component* c : reg(CK_CAMERA)) { GameObject* go = liveOwner(c); if (!go || !goActive(go)) continue; auto* cam = static_cast<Camera*>(c); if (cam->_enabled) cams.push_back(cam); }
  std::stable_sort(cams.begin(), cams.end(), [](Camera* a, Camera* b) { return a->_depth < b->_depth; });
  return cams;
}
P<Camera> Camera::get_main() {
  static Camera* cached = nullptr; static int cachedGen = -2, cachedFrame = -1;
  int key = g.camGen * 7919 + g.gen;
  if (cachedGen == key && cachedFrame == Time::_frame) return cached && !cached->_destroyed ? P<Camera>(cached) : P<Camera>();
  cachedGen = key; cachedFrame = Time::_frame; cached = nullptr;
  { auto& m = findIndex().byTag; auto it = m.find(u"MainCamera");
    if (it != m.end()) for (GameObject* go : it->second) { if (go->_destroyed || !goActive(go)) continue; for (auto& c : go->_comps) if (auto* cam = compAs<Camera>(c.get())) if (cam->_enabled) { cached = cam; return P<Camera>(cam); } } }
  return nullptr;
  for (auto& go : g.objects) {
    if (go.isNull() || go->_scene == -3 || go->_tag != "MainCamera" || !goActive(go.get())) continue;
    for (auto& c : go->_comps) if (auto* cam = compAs<Camera>(c.get())) if (cam->_enabled) return P<Camera>(cam);
  }
  return nullptr;
}
// Projection viewport (bottom-left origin, pixels). Scissor.cs sets a custom projection that keeps the
// full-screen mapping while the camera rect only clips; that is emulated here.
static void camView(const Camera* c, float& px, float& py, float& pw, float& ph) {
  float sw = c->_target.get() ? (float)c->_target->_w : (float)SCREEN_W, sh = c->_target.get() ? (float)c->_target->_h : (float)SCREEN_H;
  if (c->_customProj) { px = 0; py = 0; pw = sw; ph = sh; }
  else { px = c->_rect.x * sw; py = c->_rect.y * sh; pw = c->_rect.width * sw; ph = c->_rect.height * sh; }
}
float Camera::_viewH() const { float x, y, w, h; camView(this, x, y, w, h); return h; }
float Camera::_viewW() const { float x, y, w, h; camView(this, x, y, w, h); return w; }
Vector3 Camera::ScreenToWorldPoint(const Vector3& sp) const {
  float vx, vy, vw, vh; camView(this, vx, vy, vw, vh);
  Vector3 cp = transform->get_position(); float upp = (2 * _size) / vh;
  return Vector3(cp.x + (sp.x - (vx + vw / 2)) * upp, cp.y + (sp.y - (vy + vh / 2)) * upp, cp.z + sp.z);
}
Vector3 Camera::WorldToScreenPoint(const Vector3& w) const {
  float vx, vy, vw, vh; camView(this, vx, vy, vw, vh);
  Vector3 cp = transform->get_position(); float ppu = vh / (2 * _size);
  return Vector3(vx + vw / 2 + (w.x - cp.x) * ppu, vy + vh / 2 + (w.y - cp.y) * ppu, w.z - cp.z);
}

// ---- CPU rendering (render textures for save thumbnails)
static std::map<int, std::vector<uint8_t>> cpuTex; static std::map<int, std::pair<int, int>> cpuTexSize; static size_t cpuTexBytes = 0;
static std::map<const RenderTexture*, std::vector<uint8_t>> rtPixels;   // RGBA, top row first
static const uint8_t* cpuTexture(const engine::DrawItem& it, int& w, int& h) {
  if (it.rtex) { w = it.rtex->_w; h = it.rtex->_h; return it.rtex->_pixels.empty() ? nullptr : it.rtex->_pixels.data(); }
  auto f = cpuTex.find(it.tex);
  if (f == cpuTex.end()) {
    if (cpuTexBytes > 48u * 1024 * 1024) { cpuTex.clear(); cpuTexSize.clear(); cpuTexBytes = 0; }
    std::vector<uint8_t> px; int tw = 0, th = 0; engine::loadTexturePixels(it.tex, px, tw, th);
    cpuTexBytes += px.size(); cpuTexSize[it.tex] = { tw, th }; f = cpuTex.emplace(it.tex, std::move(px)).first;
  }
  w = cpuTexSize[it.tex].first; h = cpuTexSize[it.tex].second; return f->second.empty() ? nullptr : f->second.data();
}
void rasterizePasses(const std::vector<engine::CameraPass>& passes, std::vector<uint8_t>& fb, int W, int H, bool clearBlack) {
  if (clearBlack || fb.size() != (size_t)W * H * 4) { fb.assign((size_t)W * H * 4, 0); for (size_t i = 3; i < fb.size(); i += 4) fb[i] = 255; }
  for (auto& p : passes) {
    if (p.clear) for (int y = std::max(0, p.vy); y < std::min(H, p.vy + p.vh); y++) for (int x = std::max(0, p.vx); x < std::min(W, p.vx + p.vw); x++) {
      uint8_t* d = &fb[((size_t)y * W + x) * 4]; d[0] = (uint8_t)(p.bg[0] * 255); d[1] = (uint8_t)(p.bg[1] * 255); d[2] = (uint8_t)(p.bg[2] * 255); d[3] = 255;
    }
    auto insideMasks = [&](const std::vector<engine::DrawItem>& masks, float cutoff, int x, int y) {
      for (auto& m : masks) {
        if (x + 0.5f < m.x0 || x + 0.5f >= m.x1 || y + 0.5f < m.y0 || y + 0.5f >= m.y1) continue;
        int tw, th; const uint8_t* src = cpuTexture(m, tw, th); if (!src) continue;
        float u = m.u0 + (m.u1 - m.u0) * (((x + 0.5f) - m.x0) / (m.x1 - m.x0)), v = m.v0 + (m.v1 - m.v0) * (((y + 0.5f) - m.y0) / (m.y1 - m.y0));
        int tx = std::min(tw - 1, std::max(0, (int)(u * tw))), ty = std::min(th - 1, std::max(0, (int)(v * th)));
        if (src[((size_t)ty * tw + tx) * 4 + 3] / 255.f > cutoff) return true;
      }
      return false;
    };
    for (auto& it : p.items) {
      int tw, th; const uint8_t* src = cpuTexture(it, tw, th);
      if (!src || tw <= 0 || th <= 0) continue;
      int x0 = (int)std::floor(it.x0 + 0.5f), x1 = (int)std::floor(it.x1 + 0.5f), y0 = (int)std::floor(it.y0 + 0.5f), y1 = (int)std::floor(it.y1 + 0.5f);
      float dw = it.x1 - it.x0, dh = it.y1 - it.y0; if (dw <= 0 || dh <= 0) continue;
      for (int y = std::max(std::max(y0, p.vy), 0); y < std::min(std::min(y1, p.vy + p.vh), H); y++) {
        float v = it.v0 + (it.v1 - it.v0) * (((y + 0.5f) - it.y0) / dh); int ty = std::min(th - 1, std::max(0, (int)(v * th)));
        for (int x = std::max(std::max(x0, p.vx), 0); x < std::min(std::min(x1, p.vx + p.vw), W); x++) {
          float u = it.u0 + (it.u1 - it.u0) * (((x + 0.5f) - it.x0) / dw); int tx = std::min(tw - 1, std::max(0, (int)(u * tw)));
          if (it.maskMode) { bool in = it.maskGroup >= 0 ? insideMasks(p.groupMasks[it.maskGroup], p.groupCutoff[it.maskGroup], x, y) : insideMasks(p.masks, p.maskCutoff, x, y); if ((it.maskMode == 1) != in) continue; }
          const uint8_t* s = src + ((size_t)ty * tw + tx) * 4; float a = s[3] / 255.f * it.a; if (a <= 0) continue;
          uint8_t* d = &fb[((size_t)y * W + x) * 4];
          if (it.blend == 1) {        // multiply: dst * lerp(1, src, alpha)
            d[0] = (uint8_t)(d[0] * (1 - a + s[0] / 255.f * it.r * a)); d[1] = (uint8_t)(d[1] * (1 - a + s[1] / 255.f * it.g * a)); d[2] = (uint8_t)(d[2] * (1 - a + s[2] / 255.f * it.b * a));
          } else if (it.blend == 2) { // additive light: dst + src * alpha
            d[0] = (uint8_t)std::min(255.f, d[0] + s[0] * it.r * a); d[1] = (uint8_t)std::min(255.f, d[1] + s[1] * it.g * a); d[2] = (uint8_t)std::min(255.f, d[2] + s[2] * it.b * a);
          } else {
            d[0] = (uint8_t)(d[0] * (1 - a) + s[0] * it.r * a); d[1] = (uint8_t)(d[1] * (1 - a) + s[1] * it.g * a); d[2] = (uint8_t)(d[2] * (1 - a) + s[2] * it.b * a);
          }
        }
      }
    }
  }
}
static void buildCameraPass(Camera* cam, int W, int H, engine::CameraPass& pass);
void Camera::Render() {
  if (_target.isNull()) return;
  int W = _target->_w, H = _target->_h;
  engine::CameraPass pass; buildCameraPass(this, W, H, pass);
  std::vector<engine::CameraPass> passes{ pass };
  auto& fb = rtPixels[_target.get()];
  rasterizePasses(passes, fb, W, H, fb.size() != (size_t)W * H * 4);
}


// ======================================================================= mouse events (before Update, like Unity)
static GameObject* mouseTarget() {
  auto cams = activeCameras();
  for (int i = (int)cams.size() - 1; i >= 0; i--) {
    Camera* cam = cams[i]; if (cam->_target.get()) continue;
    float vx = cam->_rect.x * SCREEN_W, vy = cam->_rect.y * SCREEN_H, vw = cam->_viewW(), vh = cam->_viewH();
    if (g.in.mouseX < vx || g.in.mouseX >= vx + vw || g.in.mouseY < vy || g.in.mouseY >= vy + vh) continue;
    Vector3 w = cam->ScreenToWorldPoint(Vector3(g.in.mouseX, g.in.mouseY, 0));
    auto hits = queryColliders(Vector2(w.x, w.y), Vector2(w.x, w.y), cam->_mask & ~(1 << 2));
    if (!hits.empty()) return hits[0].c->gameObject.get();
  }
  return nullptr;
}
static void sendToScripts(GameObject* go, MsgFn ClassInfo::*which, const char* what) {
  if (!go || go->_destroyed) return;
  auto comps = go->_comps;
  for (auto& c : comps) if (auto* mb = compAs<MonoBehaviour>(c.get())) if (mb->_cls && mb->_enabled && !mb->_destroyed) call(mb, mb->_cls->*which, what);
}
static void mouseEvents() {
  GameObject* t = mouseTarget();
  P<GameObject> keep(t);
  if (g.hover.get() != t) {
    if (g.hover.get()) sendToScripts(g.hover.get(), &ClassInfo::OnMouseExit, "OnMouseExit");
    g.hover = P<GameObject>(t);
    if (t) sendToScripts(t, &ClassInfo::OnMouseEnter, "OnMouseEnter");
  }
  if (t && !t->_destroyed) sendToScripts(t, &ClassInfo::OnMouseOver, "OnMouseOver");
  bool down = g.in.mouse[0] && !g.prev.mouse[0], up = !g.in.mouse[0] && g.prev.mouse[0];
  if (down && t && !t->_destroyed) { g.pressed = P<GameObject>(t); sendToScripts(t, &ClassInfo::OnMouseDown, "OnMouseDown"); }
  if (up && g.pressed.get()) { sendToScripts(g.pressed.get(), &ClassInfo::OnMouseUp, "OnMouseUp"); g.pressed = nullptr; }
}

// ======================================================================= animator
// ---- compiled animation data: built once per clip / controller from the JSON (used every frame)
struct CCurveP { std::string path; std::vector<float> t; std::vector<int> spr; };
struct CCurveF { std::string path; int attr = -1, cls = 0; std::vector<float> t, v; std::vector<uint8_t> step; };   // attr: 0 m_Enabled, 1-4 m_Color r g b a
struct CClip { std::vector<CCurveP> pp; std::vector<CCurveF> fc; bool loop = false, events = false; float len = 1.0f / 60; };
static std::vector<std::unique_ptr<CClip>> g_cclips;
static const CClip& compiledClip(int idx) {
  static const CClip none;   // index out of range: the JSON gave empty values
  if (idx < 0 || idx >= (int)g.anims.size()) return none;
  if (g_cclips.size() < g.anims.size()) g_cclips.resize(g.anims.size());
  auto& slot = g_cclips[idx];
  if (!slot) {
    auto c = std::make_unique<CClip>(); const JVal& clip = g.anims[idx];
    c->loop = clip["loop"].i() != 0; c->events = clip["ev"].size() > 0;
    float l = clip["len"].f(); c->len = l > 0 ? l : 1.0f / 60;
    const JVal& pp = clip["pp"];
    for (size_t i = 0; i < pp.size(); i++) {
      const JVal& k = pp[i]["k"]; if (!k.size()) continue;
      CCurveP cp; cp.path = pp[i]["path"].str();
      for (size_t j = 0; j < k.size(); j++) { cp.t.push_back(k[j][0].f()); cp.spr.push_back(k[j][1].i()); }
      c->pp.push_back(std::move(cp));
    }
    const JVal& fc = clip["fc"];
    for (size_t i = 0; i < fc.size(); i++) {
      const JVal& k = fc[i]["k"]; if (!k.size()) continue;
      CCurveF cf; cf.path = fc[i]["path"].str(); cf.cls = fc[i]["cls"].i();
      const std::string& attr = fc[i]["attr"].str();
      if (attr == "m_Enabled") cf.attr = 0;
      else if (attr.rfind("m_Color.", 0) == 0) { char ch = attr.back(); cf.attr = ch == 'r' ? 1 : ch == 'g' ? 2 : ch == 'b' ? 3 : ch == 'a' ? 4 : -1; }
      if (cf.attr < 0) continue;   // other properties are not animated by this engine
      for (size_t j = 0; j < k.size(); j++) { cf.t.push_back(k[j][0].f()); cf.v.push_back(k[j][1].f()); float tg = k[j][3].f(); cf.step.push_back(std::isinf(tg) || std::fabs(tg) > 1e20f); }
      c->fc.push_back(std::move(cf));
    }
    slot = std::move(c);
  }
  return *slot;
}
// The objects a clip animates, found by path under the Animator; looked up again when the hierarchy changes.
static void resolveTargets(Animator* an, int clipIdx, const CClip& c) {
  GameObject* root = an->gameObject.get();
  auto target = [&](const std::string& path) -> GameObject* {
    if (path.empty()) return root;
    P<Transform> tr = root->transform->Find(String(path.c_str())); return tr.get() ? tr->gameObject.get() : nullptr;
  };
  an->_tPP.clear(); an->_tFC.clear();
  for (auto& p : c.pp) an->_tPP.push_back(target(p.path));
  for (auto& f : c.fc) an->_tFC.push_back(target(f.path));
  an->_tClip = clipIdx; an->_tGen = root && root->transform.get() ? root->transform->_subGen : 0; an->_tRoot = root;
}
static void applyClip(Animator* an, int clipIdx, float t) {
  const CClip& c = compiledClip(clipIdx);
  auto fresh = [&] { GameObject* r = an->gameObject.get(); int sg = r && r->transform.get() ? r->transform->_subGen : 0;
    if (an->_tClip != clipIdx || an->_tGen != sg || an->_tRoot != r) resolveTargets(an, clipIdx, c); };
  fresh();
  for (size_t i = 0; i < c.pp.size(); i++) {
    const CCurveP& cp = c.pp[i];
    int pick = 0; for (size_t j = 0; j < cp.t.size(); j++) if (cp.t[j] <= t + 1e-5f) pick = (int)j;
    fresh(); GameObject* go = an->_tPP[i]; if (!go) continue;
    if (auto sr = go->GetComponent<SpriteRenderer>()) sr->_sprite = getSprite(cp.spr[pick]);
  }
  for (size_t i = 0; i < c.fc.size(); i++) {
    const CCurveF& cf = c.fc[i]; size_t n = cf.t.size();
    float v = cf.v[0];
    for (size_t j = 0; j + 1 < n; j++) {
      float t0 = cf.t[j], t1 = cf.t[j + 1];
      if (t >= t0 && t <= t1) { float f = t1 > t0 ? (t - t0) / (t1 - t0) : 0; v = cf.step[j] ? cf.v[j] : cf.v[j] + (cf.v[j + 1] - cf.v[j]) * f; break; }
      if (t > t1) v = cf.v[j + 1];
    }
    fresh(); GameObject* go = an->_tFC[i]; if (!go) continue;
    int cls = cf.cls;
    if (cf.attr == 0) {
      for (auto& comp : go->_comps) {
        if (cls == 212 && compAs<SpriteRenderer>(comp.get())) static_cast<SpriteRenderer*>(comp.get())->_enabled = v > 0.5f;
        else if ((cls == 61 || cls == 60 || cls == 58) && compAs<Collider2D>(comp.get())) static_cast<Collider2D*>(comp.get())->_enabled = v > 0.5f;
        else if (cls == 114 && compAs<MonoBehaviour>(comp.get())) static_cast<MonoBehaviour*>(comp.get())->set_enabled(v > 0.5f);
      }
    } else if (auto sr = go->GetComponent<SpriteRenderer>()) {
      if (cf.attr == 1) sr->_color.r = v; else if (cf.attr == 2) sr->_color.g = v; else if (cf.attr == 3) sr->_color.b = v; else sr->_color.a = v;
    }
  }
}
struct CTrans { bool skip; float et; int to; float d; };   // skip: muted, has conditions, or no exit time; d: blend length in seconds
struct CState { int clip = 0; float sp = 1; std::vector<CTrans> tr; };
struct CCtrl { std::vector<CState> st; int def = 0; };
static std::vector<std::unique_ptr<CCtrl>> g_cctrls;
static const CCtrl& compiledCtrl(int idx) {
  static const CCtrl none;
  if (idx < 0 || idx >= (int)g.ctrls.size()) return none;
  if (g_cctrls.size() < g.ctrls.size()) g_cctrls.resize(g.ctrls.size());
  auto& slot = g_cctrls[idx];
  if (!slot) {
    auto c = std::make_unique<CCtrl>(); const JVal& layer = g.ctrls[idx]["layers"][0];
    c->def = layer["def"].i(); const JVal& states = layer["states"];
    for (size_t i = 0; i < states.size(); i++) {
      CState s; s.clip = states[i]["clip"].i(); s.sp = states[i]["sp"].f(1);
      const JVal& tr = states[i]["tr"];
      for (size_t k = 0; k < tr.size(); k++) { const JVal& t = tr[k]; s.tr.push_back({ t["mute"].i() || t["c"].i() || !t["he"].i(), t["et"].f(), t["to"].i(), t["d"].f() }); }
      c->st.push_back(std::move(s));
    }
    slot = std::move(c);
  }
  return *slot;
}
static float clipLen(int clipIdx) { if (clipIdx < 0) return 0; float l = g.anims[clipIdx]["len"].f(); return l > 0 ? l : 1.0f / 60; }
static const JVal& ctrlLayer(const Animator* an) { return g.ctrls[an->_ctrl]["layers"][0]; }
static void fireEvents(Animator* an, int clipIdx, float from, float to) {
  // events with time in (from, to]; at the very start (from < 0) include time 0
  const JVal& ev = g.anims[clipIdx]["ev"]; if (!ev.size()) return;
  float len = clipLen(clipIdx); bool loop = g.anims[clipIdx]["loop"].i() != 0;
  // times are unwrapped (they keep growing across loops); fire each event whose absolute time is in (from, to]
  std::vector<std::pair<float, size_t>> due;
  int k0 = loop ? (int)std::floor(std::max(from, 0.f) / len) : 0, k1 = loop ? (int)std::floor(to / len) : 0;
  if (k1 - k0 > 4) k0 = k1 - 4;
  for (int k = k0; k <= k1; k++)
    for (size_t i = 0; i < ev.size(); i++) {
      float et = ev[i]["t"].f(); if (!loop && et > len) continue;
      float at = k * len + et;
      if ((from < 0 ? at >= 0 : at > from) && at <= to) due.push_back({ at, i });
    }
  std::sort(due.begin(), due.end());
  GameObject* go = an->gameObject.get();
  for (auto& d : due) {
    const JVal& e = ev[d.second]; EventArg arg; arg.s = String(e["s"].str().c_str()); arg.f = e["f"].f(); arg.i = e["i"].i(); arg.has = true;
    const std::string& fn = e["fn"].str();
    auto comps = go->_comps;
    for (auto& c : comps) if (auto* mb = compAs<MonoBehaviour>(c.get())) if (mb->_cls && mb->_cls->invoke && !mb->_destroyed) {
      double t0 = profTiming ? nowMs() : 0;
      guarded(mb, fn.c_str(), [&] { mb->_cls->invoke(mb, fn.c_str(), arg); });
      if (profTiming) noteCall(nowMs() - t0, mb->_cls, "AnimEvent", fn.c_str());
    }
    if (an->_destroyed || !goActive(go)) break;
  }
}
static void animatorInit(Animator* an) {
  an->_inited = true; an->_time = 0; an->_state = an->_ctrl >= 0 ? ctrlLayer(an)["def"].i() : -1;
  an->_lastEventFrame = -1; an->_fromClip = -1;
}
void Animator::Play(const String& stateName, int, float nt) {
  if (_ctrl < 0) return;
  if (!_inited) animatorInit(this);
  std::string n = stateName.utf8(); size_t dot = n.rfind('.'); if (dot != std::string::npos) n = n.substr(dot + 1);
  const JVal& states = ctrlLayer(this)["states"];
  for (size_t i = 0; i < states.size(); i++) if (states[i]["n"].str() == n) {
    if ((int)i == _state && nt < -1e29f) return;     // already in this state: Unity does not restart
    _state = (int)i; _time = nt < -1e29f ? 0 : nt * clipLen(states[i]["clip"].i()); _lastEventFrame = -1; _fromClip = -1;
    int clip = states[i]["clip"].i(); if (clip >= 0) applyClip(this, clip, 0);
    return;
  }
  cs::log("Animator.Play: no state '%s' in %s", n.c_str(), g.ctrls[_ctrl]["n"].str().c_str());
}
AnimatorStateInfo Animator::GetCurrentAnimatorStateInfo(int) const {
  AnimatorStateInfo si; if (_ctrl < 0 || _state < 0) return si;
  const JVal& st = ctrlLayer(this)["states"][_state]; int clip = st["clip"].i(); float len = clipLen(clip);
  si._normalizedTime = len > 0 ? _time / len : 0; si._length = len / std::max(1e-6f, std::fabs(st["sp"].f(1))); si._name = String(st["n"].str().c_str());
  return si;
}
Array<AnimatorClipInfo> Animator::GetCurrentAnimatorClipInfo(int) const {
  Array<AnimatorClipInfo> a = Array<AnimatorClipInfo>::New(0);
  if (_ctrl < 0 || _state < 0) return a;
  int clip = ctrlLayer(this)["states"][_state]["clip"].i(); if (clip < 0) return a;
  AnimatorClipInfo ci; ci._clip = getClip(clip); a.vec().push_back(ci); return a;
}
P<RuntimeAnimatorController> Animator::get_runtimeAnimatorController() const { return getCtrl(_ctrl); }

static void updateAnimators(float dt) {
  std::vector<P<Animator>> list;
  for (Component* c : reg(CK_ANIMATOR)) {
    GameObject* go = liveOwner(c); if (!go) continue;
    auto* an = static_cast<Animator*>(c);
    if (!goActive(go) || !an->_enabled) { an->_inited = false; continue; }
    list.push_back(P<Animator>(an));
  }
  static const CState noState;   // what the JSON lookups gave for a state index out of range
  for (auto& anp : list) {
    Animator* an = anp.get(); if (an->_destroyed || an->_ctrl < 0) continue;
    if (!an->_inited) animatorInit(an);
    if (an->_state < 0) continue;
    if (an->_fromClip >= 0) {
      // Unity keeps playing the old state while it blends into the new one, and that state's events still fire
      // (e.g. the player's kneel_e_in fires animationAction at 0.5 s, after its transition starts at 0.42 s)
      int fc = an->_fromClip; float fp = an->_fromTime;
      an->_fromTime += dt * an->_speed * an->_fromSp;
      if (an->_fromTime >= an->_fromEnd) an->_fromClip = -1;
      if (compiledClip(fc).events) fireEvents(an, fc, fp, an->_fromTime);
      if (an->_destroyed || an->_state < 0) continue;
    }
    const CCtrl& ctrl = compiledCtrl(an->_ctrl);
    const CState& st = an->_state < (int)ctrl.st.size() ? ctrl.st[an->_state] : noState;
    int clip = st.clip; const CClip* cc = clip >= 0 ? &compiledClip(clip) : nullptr;
    float len = cc ? cc->len : 0;
    float prev = an->_lastEventFrame < 0 ? -1 : an->_time;
    float adv = dt * an->_speed * st.sp;
    if (an->_lastEventFrame >= 0) an->_time += adv;
    an->_lastEventFrame = Time::_frame;
    bool loop = cc && cc->loop;
    float local = loop ? std::fmod(an->_time, len) : std::min(an->_time, len);
    if (cc) { applyClip(an, clip, local); if (cc->events) fireEvents(an, clip, prev, an->_time); }
    if (an->_destroyed) continue;
    // exit-time transitions without conditions
    float nt = len > 0 ? an->_time / len : 1;
    for (const CTrans& t : st.tr) {
      if (t.skip) continue;
      if (nt >= t.et) {
        int to = t.to; if (to < 0) to = ctrl.def;
        float end = t.et * len + t.d * st.sp;   // old clip's time when the blend ends
        if (cc && cc->events && an->_time < end) { an->_fromClip = clip; an->_fromTime = an->_time; an->_fromEnd = end; an->_fromSp = st.sp; }
        else an->_fromClip = -1;
        an->_state = to; an->_time = 0; an->_lastEventFrame = -1;
        int nc = to < (int)ctrl.st.size() ? ctrl.st[to].clip : 0; if (nc >= 0) applyClip(an, nc, 0);
        break;
      }
    }
  }
}

// ======================================================================= audio (playback state; mixing added when decoders are in)
float AudioListener::_volume = 1; bool AudioListener::_pause = false;
void AudioListener::set_pause(bool p) { _pause = p; }
static int voiceFor(AudioSource* s) { for (size_t i = 0; i < g.voices.size(); i++) if (g.voices[i].src.get() == s && !g.voices[i].oneShot) return (int)i; return -1; }
static void startVoice(AudioSource* a, int clip, float delay, bool oneShot, float vs) {
  Voice v{ clip, Time::_time + delay, a->_pitch, oneShot ? false : a->_loop, oneShot, P<AudioSource>(a), a->_volume * vs };
  v.mix = audio::play(clip, a->_mute ? 0.f : v.volume, a->_pitch, a->_pan, v.loop, delay, a->_ignorePause, a->_ignoreVolume);
  g.voices.push_back(v);
}
void AudioSource::Play() { Stop(); if (_clip.isNull()) return; startVoice(this, _clip->_index, 0, false, 1); }
void AudioSource::PlayDelayed(float d) { Stop(); if (_clip.isNull()) return; startVoice(this, _clip->_index, d > 0 ? d : 0, false, 1); }
void AudioSource::Stop() {
  for (auto& v : g.voices) if (v.src.get() == this && !v.oneShot && v.mix >= 0) audio::stop(v.mix);
  g.voices.erase(std::remove_if(g.voices.begin(), g.voices.end(), [&](const Voice& v) { return v.src.get() == this && !v.oneShot; }), g.voices.end());
}
void AudioSource::PlayOneShot(const P<AudioClip>& clip, float vs) { if (clip.isNull()) return; startVoice(this, clip->_index, 0, true, vs); }
bool AudioSource::get_isPlaying() const {
  for (auto& v : g.voices) if (v.src.get() == this && !v.oneShot) { if (v.loop) return true; float len = g.audio[v.clip]["len"].f(); return Time::_time - v.start < len / std::max(0.01f, std::fabs(v.pitch)); }
  return false;
}
float AudioSource::get_time() const { for (auto& v : g.voices) if (v.src.get() == this && !v.oneShot) { float len = g.audio[v.clip]["len"].f(); float t = (Time::_time - v.start) * v.pitch; return v.loop && len > 0 ? std::fmod(t, len) : t; } return 0; }
void AudioSource::set_time(float t) { int v = voiceFor(this); if (v >= 0) { g.voices[v].start = Time::_time - t / std::max(0.01f, g.voices[v].pitch); if (g.voices[v].mix >= 0) audio::seek(g.voices[v].mix, t); } }
void AudioSource::set_volume(float v) { if (v == _volume) return; _volume = v; int i = voiceFor(this); if (i >= 0) { g.voices[i].volume = v; if (g.voices[i].mix >= 0) audio::setVolume(g.voices[i].mix, _mute ? 0.f : v); } }
void AudioSource::set_pitch(float p) { if (p == _pitch) return; _pitch = p; int i = voiceFor(this); if (i >= 0) { g.voices[i].pitch = p; if (g.voices[i].mix >= 0) audio::setPitch(g.voices[i].mix, p); } }
void AudioSource::set_panStereo(float p) { if (p == _pan) return; _pan = p; int i = voiceFor(this); if (i >= 0 && g.voices[i].mix >= 0) audio::setPan(g.voices[i].mix, p); }
void AudioSource::set_loop(bool l) { _loop = l; int i = voiceFor(this); if (i >= 0) { g.voices[i].loop = l; if (g.voices[i].mix >= 0) audio::setLoop(g.voices[i].mix, l); } }
static void reapVoices() {
  g.voices.erase(std::remove_if(g.voices.begin(), g.voices.end(), [](const Voice& v) {
    bool dead = v.src.isNull();
    if (!dead && !v.loop) { float len = g.audio[v.clip]["len"].f(); dead = Time::_time - v.start > len / std::max(0.01f, std::fabs(v.pitch)) + 0.1f; }
    if (dead && v.mix >= 0) audio::stop(v.mix);
    return dead; }), g.voices.end());
  audio::setListener(AudioListener::_volume, AudioListener::_pause);
}
void engine::mixAudio(int16_t* out, int frames, int rate) { audio::mix(out, frames, rate); }

// ======================================================================= misc services
float Time::_dt = 1.0f / 60, Time::_time = 0; int Time::_frame = 0;
P<RenderTexture> RenderTexture::_active;
static uint32_t rngState = 0x12345678;
static uint32_t rng() { rngState ^= rngState << 13; rngState ^= rngState >> 17; rngState ^= rngState << 5; return rngState; }
int Random::Range(int a, int b) { if (b <= a) return a; return a + (int)(rng() % (uint32_t)(b - a)); }
float Random::Range(float a, float b) { return a + (b - a) * (rng() / 4294967295.0f); }
float Random::get_value() { return rng() / 4294967295.0f; }
void Random::set_seed(int s) { rngState = (uint32_t)s ? (uint32_t)s : 1; }
int Random::get_seed() { return (int)rngState; }

static bool keyState(const InputState& s, KeyCode k) { int i = (int)k; return i >= 0 && i < 512 && s.keys[i]; }
bool Input::GetKey(KeyCode k) { return keyState(g.in, k); }
KeyCode Input::_keyFromName(const String& n) { std::string s = n.ToLower().utf8(); if (s.size() == 1 && s[0] >= 'a' && s[0] <= 'z') return (KeyCode)(int)s[0]; if (s == "space") return KeyCode::Space; if (s == "escape") return KeyCode::Escape; if (s == "return" || s == "enter") return KeyCode::Return; return KeyCode::None; }
bool Input::GetKeyDown(KeyCode k) { return keyState(g.in, k) && !keyState(g.prev, k); }
bool Input::GetKeyUp(KeyCode k) { return !keyState(g.in, k) && keyState(g.prev, k); }
bool Input::GetMouseButton(int b) { return b >= 0 && b < 3 && g.in.mouse[b]; }
bool Input::GetMouseButtonDown(int b) { return b >= 0 && b < 3 && g.in.mouse[b] && !g.prev.mouse[b]; }
bool Input::GetMouseButtonUp(int b) { return b >= 0 && b < 3 && !g.in.mouse[b] && g.prev.mouse[b]; }
Vector3 Input::get_mousePosition() { return Vector3(g.in.mouseX, g.in.mouseY, 0); }
int Screen::get_width() { return SCREEN_W; }
int Screen::get_height() { return SCREEN_H; }

void Application::Quit() { g.quit = true; }
String Application::get_persistentDataPath() { return String(g.save.c_str()); }

static void savePrefs() {
  std::string p = g.save + "/prefs.txt"; FILE* f = fopen(p.c_str(), "wb"); if (!f) return;
  for (auto& kv : g.prefs) fprintf(f, "%s\t%s\n", kv.first.c_str(), kv.second.c_str());
  fclose(f); g.prefsDirty = false;
}
static void loadPrefs() {
  std::string s = readFile(g.save + "/prefs.txt"); size_t i = 0;
  while (i < s.size()) { size_t e = s.find('\n', i); if (e == std::string::npos) e = s.size(); std::string line = s.substr(i, e - i); size_t tab = line.find('\t'); if (tab != std::string::npos) g.prefs[line.substr(0, tab)] = line.substr(tab + 1); i = e + 1; }
}
// stored as "i:123", "f:1.5", "s:text" (text has \n and \t escaped)
static std::string esc(const std::string& s) { std::string o; for (char c : s) { if (c == '\n') o += "\\n"; else if (c == '\t') o += "\\t"; else if (c == '\\') o += "\\\\"; else o += c; } return o; }
static std::string unesc(const std::string& s) { std::string o; for (size_t i = 0; i < s.size(); i++) { if (s[i] == '\\' && i + 1 < s.size()) { char n = s[++i]; o += n == 'n' ? '\n' : n == 't' ? '\t' : n; } else o += s[i]; } return o; }
void PlayerPrefs::SetInt(const String& k, int v) { g.prefs[k.utf8()] = "i:" + std::to_string(v); g.prefsDirty = true; }
int PlayerPrefs::GetInt(const String& k, int d) { auto it = g.prefs.find(k.utf8()); if (it == g.prefs.end() || it->second.rfind("i:", 0) != 0) return d; return atoi(it->second.c_str() + 2); }
void PlayerPrefs::SetFloat(const String& k, float v) { char b[32]; snprintf(b, sizeof b, "f:%.9g", v); g.prefs[k.utf8()] = b; g.prefsDirty = true; }
float PlayerPrefs::GetFloat(const String& k, float d) { auto it = g.prefs.find(k.utf8()); if (it == g.prefs.end() || it->second.rfind("f:", 0) != 0) return d; return (float)atof(it->second.c_str() + 2); }
void PlayerPrefs::SetString(const String& k, const String& v) { g.prefs[k.utf8()] = "s:" + esc(v.utf8()); g.prefsDirty = true; }
String PlayerPrefs::GetString(const String& k, const String& d) { auto it = g.prefs.find(k.utf8()); if (it == g.prefs.end() || it->second.rfind("s:", 0) != 0) return d; return String(unesc(it->second.substr(2)).c_str()); }
bool PlayerPrefs::HasKey(const String& k) { return g.prefs.count(k.utf8()) != 0; }
void PlayerPrefs::DeleteKey(const String& k) { g.prefs.erase(k.utf8()); g.prefsDirty = true; }
void PlayerPrefs::Save() { savePrefs(); }

void Debug::Log(const String& s) { cs::log("[log] %s", s.utf8().c_str()); }
void Debug::LogWarning(const String& s) { cs::log("[warn] %s", s.utf8().c_str()); }
void Debug::LogError(const String& s) { cs::log("[error] %s", s.utf8().c_str()); }

String Scene::get_name() const { return _index >= 0 ? String(g.manifest["scenes"][_index].str().c_str()) : String::Empty; }
Scene SceneManager::GetActiveScene() { Scene s; s._index = g.activeScene; return s; }
void SceneManager::LoadScene(int i) { g.pendingScene = i; }
void SceneManager::LoadScene(const String& name) {
  std::string n = name.utf8(); const JVal& sc = g.manifest["scenes"];
  for (size_t i = 0; i < sc.size(); i++) if (sc[i].str() == n) { g.pendingScene = (int)i; return; }
  cs::log("LoadScene: no scene named %s", n.c_str());
}

int LayerMask::NameToLayer(const String& n) { std::string s = n.utf8(); for (size_t i = 0; i < g.layerNames.size(); i++) if (g.layerNames[i] == s) return (int)i; return -1; }
int LayerMask::GetMask(std::initializer_list<String> names) { int m = 0; for (auto& n : names) { int l = NameToLayer(n); if (l >= 0) m |= 1 << l; } return m; }

P<Shader> Shader::Find(const String& name) { P<Shader> s(new Shader()); s->_name = name; return s; }
P<Sprite> Sprite::Create(const P<Texture2D>& t, const Rect& r, const Vector2& pivot, float ppu) {
  P<Sprite> s(new Sprite()); s->_tex = t; s->_rect = r; s->_ppu = ppu; s->_pivotN = Vector2(r.width ? pivot.x : 0.5f, r.height ? pivot.y : 0.5f); return s;
}
Bounds Sprite::get_bounds() const { Bounds b; b.size = Vector3(_rect.width / _ppu, _rect.height / _ppu, 0); b.center = Vector3((0.5f - _pivotN.x) * b.size.x, (0.5f - _pivotN.y) * b.size.y, 0); return b; }
Bounds Renderer::get_bounds() const { Bounds b; b.center = transform->get_position(); return b; }
Bounds SpriteRenderer::get_bounds() const {
  Bounds b; if (_sprite.isNull()) { b.center = transform->get_position(); return b; }
  Bounds lb = _sprite->get_bounds(); Vector3 p = transform->get_position(), s = transform->get_lossyScale();
  b.center = Vector3(p.x + lb.center.x * s.x, p.y + lb.center.y * s.y, p.z); b.size = Vector3(std::fabs(lb.size.x * s.x), std::fabs(lb.size.y * s.y), 0); return b;
}
Matrix4x4 Matrix4x4::TRS(const Vector3& t, const Quaternion&, const Vector3& s) { Matrix4x4 m; m.m[0] = s.x; m.m[5] = s.y; m.m[10] = s.z; m.m[12] = t.x; m.m[13] = t.y; m.m[14] = t.z; return m; }
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& o) const { Matrix4x4 r; for (int c = 0; c < 4; c++) for (int rr = 0; rr < 4; rr++) { float v = 0; for (int k = 0; k < 4; k++) v += m[k * 4 + rr] * o.m[c * 4 + k]; r.m[c * 4 + rr] = v; } return r; }
String Vector2::ToString() const { char b[64]; snprintf(b, sizeof b, "(%.1f, %.1f)", x, y); return String(b); }
String Vector3::ToString() const { char b[96]; snprintf(b, sizeof b, "(%.1f, %.1f, %.1f)", x, y, z); return String(b); }

void Texture2D::ReadPixels(const Rect& src, int dx, int dy, bool) {
  // source: the active render texture (bottom-left origin coordinates, like Unity)
  RenderTexture* rt = RenderTexture::_active.get(); if (!rt) return;
  auto it = rtPixels.find(rt); if (it == rtPixels.end()) return;
  const std::vector<uint8_t>& s = it->second; int SW = rt->_w, SH = rt->_h;
  if (_pixels.size() != (size_t)_w * _h * 4) _pixels.assign((size_t)_w * _h * 4, 0);
  int sx0 = (int)src.x, sy0 = (int)src.y, w = (int)src.width, h = (int)src.height;
  for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) {
    int sx = sx0 + x, sy = sy0 + y, tx = dx + x, ty = dy + y;
    if (sx < 0 || sy < 0 || sx >= SW || sy >= SH || tx < 0 || ty < 0 || tx >= _w || ty >= _h) continue;
    const uint8_t* p = &s[((size_t)(SH - 1 - sy) * SW + sx) * 4]; uint8_t* d = &_pixels[((size_t)(_h - 1 - ty) * _w + tx) * 4];
    d[0] = p[0]; d[1] = p[1]; d[2] = p[2]; d[3] = 255;
  }
  _dirty = true;
}
static uint32_t pngCrc(const uint8_t* p, size_t n, uint32_t c = 0xffffffff) {
  static uint32_t t[256]; if (!t[1]) for (uint32_t i = 0; i < 256; i++) { uint32_t k = i; for (int j = 0; j < 8; j++) k = k & 1 ? 0xedb88320 ^ (k >> 1) : k >> 1; t[i] = k; }
  for (size_t i = 0; i < n; i++) c = t[(c ^ p[i]) & 255] ^ (c >> 8); return c;
}
static void pngBe32(std::vector<uint8_t>& o, uint32_t v) { o.push_back(v >> 24); o.push_back(v >> 16); o.push_back(v >> 8); o.push_back(v); }
static void pngChunk(std::vector<uint8_t>& o, const char* type, const std::vector<uint8_t>& d) {
  pngBe32(o, (uint32_t)d.size()); size_t s = o.size(); o.insert(o.end(), type, type + 4); o.insert(o.end(), d.begin(), d.end());
  pngBe32(o, pngCrc(&o[s], d.size() + 4) ^ 0xffffffff);
}
Array<uint8_t> ImageConversion::EncodeToPNG(const P<Texture2D>& t) {
  int W = t->_w, H = t->_h; std::vector<uint8_t> raw;
  for (int y = 0; y < H; y++) { raw.push_back(0); for (int x = 0; x < W; x++) { size_t i = ((size_t)y * W + x) * 4; for (int k = 0; k < 4; k++) raw.push_back(i + k < t->_pixels.size() ? t->_pixels[i + k] : 0); } }
  std::vector<uint8_t> z = { 0x78, 0x01 }; uint32_t a = 1, b = 0;
  for (size_t i = 0; i < raw.size(); i += 65535) {
    size_t n = std::min<size_t>(65535, raw.size() - i); z.push_back(i + n == raw.size() ? 1 : 0);
    z.push_back(n & 255); z.push_back(n >> 8); z.push_back(~n & 255); z.push_back((~n >> 8) & 255);
    z.insert(z.end(), raw.begin() + i, raw.begin() + i + n);
  }
  for (uint8_t c : raw) { a = (a + c) % 65521; b = (b + a) % 65521; } pngBe32(z, (b << 16) | a);
  std::vector<uint8_t> o = { 0x89, 'P', 'N', 'G', 13, 10, 26, 10 }, hdr; pngBe32(hdr, W); pngBe32(hdr, H); hdr.push_back(8); hdr.push_back(6); hdr.push_back(0); hdr.push_back(0); hdr.push_back(0);
  pngChunk(o, "IHDR", hdr); pngChunk(o, "IDAT", z); pngChunk(o, "IEND", {});
  Array<uint8_t> out = Array<uint8_t>::New((int)o.size()); memcpy(out.vec().data(), o.data(), o.size()); return out;
}
bool ImageConversion::LoadImage(const P<Texture2D>& t, const Array<uint8_t>& bytes) {
  Array<uint8_t> in = bytes; if (in.Length() < 33) return false;
  const uint8_t* p = in.vec().data(); size_t n = in.Length();
  if (p[0] != 0x89 || p[1] != 'P') return false;
  size_t o = 8; int W = 0, H = 0, depth = 0, ct = 0; std::vector<uint8_t> idat;
  while (o + 8 <= n) {
    uint32_t len = (p[o] << 24) | (p[o + 1] << 16) | (p[o + 2] << 8) | p[o + 3]; const uint8_t* d = p + o + 8;
    if (!memcmp(p + o + 4, "IHDR", 4)) { W = (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | d[3]; H = (d[4] << 24) | (d[5] << 16) | (d[6] << 8) | d[7]; depth = d[8]; ct = d[9]; }
    else if (!memcmp(p + o + 4, "IDAT", 4)) idat.insert(idat.end(), d, d + len);
    else if (!memcmp(p + o + 4, "IEND", 4)) break;
    o += 12 + len;
  }
  int ch = ct == 6 ? 4 : ct == 2 ? 3 : 0; if (!ch || depth != 8 || W <= 0 || H <= 0) return false;
  std::vector<uint8_t> raw; if (!inflate_ns::zlibInflate(idat.data(), idat.size(), raw)) return false;
  size_t stride = (size_t)W * ch; if (raw.size() < (stride + 1) * H) return false;
  std::vector<uint8_t> px(stride * H), prev(stride, 0);
  for (int y = 0; y < H; y++) {
    uint8_t f = raw[y * (stride + 1)]; const uint8_t* line = &raw[y * (stride + 1) + 1]; uint8_t* out = &px[y * stride];
    for (size_t x = 0; x < stride; x++) {
      int a = x >= (size_t)ch ? out[x - ch] : 0, b = prev[x], c = x >= (size_t)ch ? prev[x - ch] : 0, v = line[x];
      if (f == 1) v += a; else if (f == 2) v += b; else if (f == 3) v += (a + b) >> 1;
      else if (f == 4) { int pp = a + b - c, pa = std::abs(pp - a), pb = std::abs(pp - b), pc = std::abs(pp - c); v += pa <= pb && pa <= pc ? a : pb <= pc ? b : c; }
      out[x] = (uint8_t)v;
    }
    memcpy(prev.data(), out, stride);
  }
  t->_w = W; t->_h = H; t->_pixels.assign((size_t)W * H * 4, 255);
  for (size_t i = 0; i < (size_t)W * H; i++) for (int k = 0; k < ch; k++) t->_pixels[i * 4 + k] = px[i * ch + k];
  t->_dirty = true; return true;
}


static std::string mapPath(const String& p) { return p.utf8(); }
P<FileStream> File::Open(const String& p, FileMode m) { return P<FileStream>(new FileStream(mapPath(p), m)); }
bool File::Exists(const String& p) { FILE* f = fopen(mapPath(p).c_str(), "rb"); if (f) fclose(f); return f != nullptr; }
void File::Delete(const String& p) { remove(mapPath(p).c_str()); }
void File::WriteAllBytes(const String& p, const Array<uint8_t>& d) { FILE* f = fopen(mapPath(p).c_str(), "wb"); if (!f) return; Array<uint8_t> a = d; if (a.Length()) fwrite(a.vec().data(), 1, a.Length(), f); fclose(f); }
Array<uint8_t> File::ReadAllBytes(const String& p) { if (!File::Exists(p)) throw Exception("FileNotFoundException: " + mapPath(p)); std::string s = readFile(mapPath(p)); Array<uint8_t> a = Array<uint8_t>::New((int)s.size()); if (!s.empty()) memcpy(a.vec().data(), s.data(), s.size()); return a; }

// ======================================================================= Resources
P<Object> Resources::Load(const String& path) {
  // untyped: the main asset (prefab, texture, audio, text) before sub-assets like sprites
  static const char* order[] = { "prefab", "tex", "audio", "text", "ctrl", "anim", "sprite" };
  for (const char* k : order) { P<Object> o = _load(path, k); if (o.get()) return o; }
  return nullptr;
}
// Unity Resources paths are case-insensitive: look them up in lower case
static std::string lowerPath(const String& path) { std::string p = path.ToLower().utf8(); for (auto& c : p) if (c == 0x5c) c = 0x2f; while (!p.empty() && p.back() == 0x2f) p.pop_back(); return p; }
static std::unordered_map<std::string, const JVal*>& resIndex() {
  static std::unordered_map<std::string, const JVal*> m;
  if (m.empty()) for (size_t i = 0; i < g.resources.k.size(); i++) { String k = String(g.resources.k[i].c_str()); m[lowerPath(k)] = &g.resources.a[i]; }
  return m;
}
P<Object> Resources::_load(const String& path, const char* kind) {
  auto it = resIndex().find(lowerPath(path)); if (it == resIndex().end()) return nullptr;
  const JVal& list = *it->second;
  for (size_t i = 0; i < list.size(); i++) if (!*kind || list[i][0].str() == kind) return assetByKind(list[i][0].str(), list[i][1].i());
  return nullptr;
}
std::vector<P<Object>> Resources::_loadAll(const String& path, const char* kind) {
  // Results are cached: the resource list and the asset objects it returns never change after start-up, and every
  // call scanned the whole resource index (each text field loads its font this way).
  static std::map<std::pair<std::string, std::string>, std::vector<P<Object>>> cache;
  std::string p = lowerPath(path);
  std::pair<std::string, std::string> key(p, kind ? kind : "");
  { auto c = cache.find(key); if (c != cache.end()) return c->second; }
  std::vector<P<Object>> out;
  std::vector<std::pair<std::string, const JVal*>> matches;
  for (auto& kv : resIndex()) {
    const std::string& key = kv.first;
    if (p.empty() || key == p || (key.size() > p.size() && key.compare(0, p.size(), p) == 0 && key[p.size()] == 0x2f)) matches.push_back(kv);
  }
  std::sort(matches.begin(), matches.end(), [](const std::pair<std::string, const JVal*>& x, const std::pair<std::string, const JVal*>& y) { return x.first < y.first; });
  for (auto& m : matches) { const JVal& list = *m.second; for (size_t j = 0; j < list.size(); j++) if (!*kind || list[j][0].str() == kind) out.push_back(assetByKind(list[j][0].str(), list[j][1].i())); }
  cache[key] = out;
  return out;
}

// ======================================================================= textures for the renderer
bool engine::loadTexturePixels(int ki, std::vector<uint8_t>& rgba, int& w, int& h, const char** why) {
  const char* dummy; if (!why) why = &dummy;
  std::string s = readFile(g.data + "/tex/" + std::to_string(ki) + ".dtx");
  if (s.empty()) { *why = "file missing or unreadable"; return false; }
  if (s.size() < 16 || memcmp(s.data(), "DTX1", 4)) { *why = "bad header (file damaged)"; return false; }
  uint32_t W, H, raw; memcpy(&W, s.data() + 4, 4); memcpy(&H, s.data() + 8, 4); memcpy(&raw, s.data() + 12, 4);
#ifdef VITA
  // zlib's inflate is several times faster than inflate.h on the Vita's CPU (area loads, save thumbnails)
  rgba.resize(raw); uLongf outLen = raw;
  if (uncompress(rgba.data(), &outLen, (const Bytef*)s.data() + 16, (uLong)(s.size() - 16)) != Z_OK || outLen != raw) { *why = "pixel data damaged"; return false; }
#else
  if (!inflate_ns::zlibInflate((const uint8_t*)s.data() + 16, s.size() - 16, rgba, raw) || rgba.size() != raw) { *why = "pixel data damaged"; return false; }
#endif
  if ((uint64_t)W * H * 4 != raw) { *why = "size mismatch"; return false; }
  w = (int)W; h = (int)H; return true;
}
int engine::textureFilter(int ki) { return g.textures[ki]["fm"].i(); }
int engine::textureCount() { return (int)g.textures.size(); }
const char* engine::textureName(int ki) { static std::string n; n = ki >= 0 && ki < (int)g.textures.size() ? g.textures[ki]["n"].str() : std::string("?"); return n.c_str(); }
int engine::sceneLoadCount() { return g_sceneLoads; }

// ======================================================================= frame building

struct RItem { SpriteRenderer* sr; int sl, so; float z; int order; GameObject* group; int gsl, gso; float gz; int ci; int layer; };
static std::vector<GameObject*> g_sortGroups;   // objects with an enabled SortingGroup, gathered by collectRenderers
static GameObject* sortingGroupOf(GameObject* go) {
  if (g_sortGroups.empty()) return nullptr;
  for (Transform* t = go->transform.get(); t; t = t->_parent) {
    GameObject* x = t->gameObject.get(); if (!x) break;
    for (GameObject* s : g_sortGroups) if (s == x) return x;
  }
  return nullptr;
}
static void gatherSortGroups() {
  g_sortGroups.clear();
  for (Component* c : reg(CK_SORTGROUP)) { GameObject* go = liveOwner(c); if (go && static_cast<SortingGroup*>(c)->_enabled) g_sortGroups.push_back(go); }
}
static std::vector<RItem> collectRenderers() {
  std::vector<RItem> all;
  gatherSortGroups();
  for (Component* c : reg(CK_SPRITE)) {
    GameObject* go = liveOwner(c); if (!go || !goActive(go)) continue;
    auto* sr = static_cast<SpriteRenderer*>(c);
    {
      if (!sr->_enabled || sr->_sprite.isNull() || sr->_color.a <= 0) continue;
      if (sr->_slKey != sr->_sortingLayer) { auto it = g.sortingLayerOrder.find(sr->_sortingLayer); sr->_slOrder = it == g.sortingLayerOrder.end() ? 0 : it->second; sr->_slKey = sr->_sortingLayer; }
      RItem r{ sr, sr->_slOrder, sr->_sortingOrder, go->transform->get_position().z, (int)go->_serial, sortingGroupOf(go), 0, 0, 0 };
      if (r.group) { SortingGroup* sg = r.group->GetComponent<SortingGroup>().get(); r.gsl = 0; r.gso = sg ? sg->_sortingOrder : 0; r.gz = r.group->transform->get_position().z; }
      else { r.gsl = r.sl; r.gso = r.so; r.gz = r.z; }
      r.ci = 0; r.layer = go->_layer;
      all.push_back(r);
    }
  }
  // A SortingGroup sorts as one unit at the group's position; its members sort among themselves inside it.
  // Object order + component index make this a total order, so any sort gives the same list. Starting from
  // last frame's order, an insertion sort only moves what changed.
  auto less = [](const RItem& a, const RItem& b) {
    if (a.gsl != b.gsl) return a.gsl < b.gsl; if (a.gso != b.gso) return a.gso < b.gso; if (a.gz != b.gz) return a.gz > b.gz;
    if (a.group != b.group) return a.group < b.group;
    if (a.sl != b.sl) return a.sl < b.sl; if (a.so != b.so) return a.so < b.so; if (a.z != b.z) return a.z > b.z;
    if (a.order != b.order) return a.order < b.order; return compIndex(a.sr) < compIndex(b.sr); };
  static unsigned stamp = 0; static size_t lastN = 0;
  std::vector<RItem> known, fresh; known.reserve(all.size());
  for (auto& r : all) (r.sr->_sortStamp == stamp && stamp) ? known.push_back(r) : fresh.push_back(r);
  if (fresh.size() * 4 > all.size()) std::sort(all.begin(), all.end(), less);
  else {
    // last frame's order: positions are unique, so each known item goes straight back to its old place
    std::vector<const RItem*> place(lastN, nullptr);
    for (auto& r : known) if (r.sr->_sortPos >= 0 && (size_t)r.sr->_sortPos < lastN) place[r.sr->_sortPos] = &r;
    std::vector<RItem> ordered; ordered.reserve(all.size());
    for (const RItem* p : place) if (p) ordered.push_back(*p);
    ordered.insert(ordered.end(), fresh.begin(), fresh.end());
    all = std::move(ordered);
    for (size_t i = 1; i < all.size(); i++) { RItem x = all[i]; size_t j = i; while (j > 0 && less(x, all[j - 1])) { all[j] = all[j - 1]; j--; } all[j] = x; }
  }
  stamp++; lastN = all.size();
  for (size_t i = 0; i < all.size(); i++) { all[i].sr->_sortPos = (int)i; all[i].sr->_sortStamp = stamp; }
  return all;
}
static bool spriteQuad(Sprite* sp, Transform* tr, bool flipX, bool flipY, float ox, float oy, float left, float top, float ppu, engine::DrawItem& d) {
  Texture2D* tex = sp->_tex.get(); if (!tex || tex->_w <= 0) return false;
  Vector3 p = tr->get_position(), s = tr->get_lossyScale();
  float w = sp->_rect.width / sp->_ppu, h = sp->_rect.height / sp->_ppu;
  float lx0 = -sp->_pivotN.x * w, lx1 = lx0 + w, ly0 = -sp->_pivotN.y * h, ly1 = ly0 + h;
  if (flipX) { float t = lx0; lx0 = -lx1; lx1 = -t; }
  if (flipY) { float t = ly0; ly0 = -ly1; ly1 = -t; }
  float wx0 = p.x + lx0 * s.x, wx1 = p.x + lx1 * s.x, wy0 = p.y + ly0 * s.y, wy1 = p.y + ly1 * s.y;
  d.tex = tex->_texIndex; d.rtex = tex->_texIndex < 0 ? tex : nullptr;
  d.x0 = ox + (wx0 - left) * ppu; d.x1 = ox + (wx1 - left) * ppu;
  d.y0 = oy + (top - wy1) * ppu; d.y1 = oy + (top - wy0) * ppu;
  float u0 = sp->_rect.x / tex->_w, u1 = (sp->_rect.x + sp->_rect.width) / tex->_w;
  float v0 = 1 - (sp->_rect.y + sp->_rect.height) / tex->_h, v1 = 1 - sp->_rect.y / tex->_h;
  bool fx = flipX != (s.x < 0), fy = flipY != (s.y < 0);
  if (d.x0 > d.x1) std::swap(d.x0, d.x1);
  if (d.y0 > d.y1) std::swap(d.y0, d.y1);
  d.u0 = fx ? u1 : u0; d.u1 = fx ? u0 : u1; d.v0 = fy ? v1 : v0; d.v1 = fy ? v0 : v1;
  d.linear = tex->_filter != FilterMode::Point;
  return true;
}
// spriteQuad for a SpriteRenderer, reusing the last result for this camera when none of its inputs changed
static bool cachedQuad(SpriteRenderer* sr, Camera* cam, float ox, float oy, float left, float top, float ppu, engine::DrawItem& d) {
  Sprite* sp = sr->_sprite.get(); Transform* tr = sr->transform.get();
  if (!sp || !tr) return spriteQuad(sp, tr, sr->_flipX, sr->_flipY, ox, oy, left, top, ppu, d);
  Texture2D* tex = sp->_tex.get();
  tr->_updateWorld();
  int slot = sr->_qc[0].cam == cam ? 0 : sr->_qc[1].cam == cam ? 1 : -1;
  if (slot >= 0) {
    const auto& q = sr->_qc[slot];
    if (q.tr == tr && q.sp == sp && q.tex == tex && q.wVer == tr->_wVer && q.fx == sr->_flipX && q.fy == sr->_flipY &&
        q.ox == ox && q.oy == oy && q.left == left && q.top == top && q.ppu == ppu &&
        (!tex || (q.tw == tex->_w && q.th == tex->_h && q.filt == (int)tex->_filter))) {
      if (!q.ok) return false;
      d.tex = q.texIndex; d.rtex = q.texIndex < 0 ? (Texture2D*)q.tex : nullptr;
      d.x0 = q.x0; d.y0 = q.y0; d.x1 = q.x1; d.y1 = q.y1; d.u0 = q.u0; d.v0 = q.v0; d.u1 = q.u1; d.v1 = q.v1; d.linear = q.linear;
      return true;
    }
  } else { slot = sr->_qcNext; sr->_qcNext ^= 1; }
  bool ok = spriteQuad(sp, tr, sr->_flipX, sr->_flipY, ox, oy, left, top, ppu, d);
  auto& q = sr->_qc[slot];
  q.cam = cam; q.tr = tr; q.sp = sp; q.tex = tex; q.wVer = tr->_wVer; q.fx = sr->_flipX; q.fy = sr->_flipY;
  q.ox = ox; q.oy = oy; q.left = left; q.top = top; q.ppu = ppu;
  q.tw = tex ? tex->_w : 0; q.th = tex ? tex->_h : 0; q.filt = tex ? (int)tex->_filter : 0; q.ok = ok;
  if (ok) { q.texIndex = d.tex; q.x0 = d.x0; q.y0 = d.y0; q.x1 = d.x1; q.y1 = d.y1; q.u0 = d.u0; q.v0 = d.v0; q.u1 = d.u1; q.v1 = d.v1; q.linear = d.linear; }
  return ok;
}
static void buildCameraPassFrom(Camera* cam, int W, int H, engine::CameraPass& pass, const std::vector<RItem>& all) {
  float pvx, pvy, pvw, pvh; camView(cam, pvx, pvy, pvw, pvh);          // projection area, bottom-left origin
  pass.clear = cam->_clear == CameraClearFlags::SolidColor || cam->_clear == CameraClearFlags::Skybox;
  pass.bg[0] = cam->_bg.r; pass.bg[1] = cam->_bg.g; pass.bg[2] = cam->_bg.b; pass.bg[3] = 1;
  pass.vx = (int)(cam->_rect.x * W); pass.vw = (int)(cam->_rect.width * W);   // clip area, top-left origin
  pass.vh = (int)(cam->_rect.height * H); pass.vy = H - (int)(cam->_rect.y * H) - pass.vh;
  Vector3 cp = cam->transform->get_position(); float ppu = pvh / (2 * cam->_size);
  float left = cp.x - (pvw / 2) / ppu, top = cp.y + (pvh / 2) / ppu;
  float ox = pvx, oy = H - (pvy + pvh);
  bool anyMasked = false; std::map<GameObject*, int> groupIndex;
  for (auto& it : all) {
    if (!(cam->_mask & (1 << it.layer))) continue;
    engine::DrawItem d;
    if (!cachedQuad(it.sr, cam, ox, oy, left, top, ppu, d)) continue;
    if (d.x1 <= pass.vx || d.x0 >= pass.vx + pass.vw || d.y1 <= pass.vy || d.y0 >= pass.vy + pass.vh) continue;   // off screen
    d.r = it.sr->_color.r; d.g = it.sr->_color.g; d.b = it.sr->_color.b; d.a = it.sr->_color.a;
    d.maskMode = (uint8_t)it.sr->_mask; if (d.maskMode) anyMasked = true;
    d.blend = it.sr->_material.get() ? (uint8_t)it.sr->_material->_blend : 0;
    if (it.group) { auto gi = groupIndex.find(it.group); if (gi == groupIndex.end()) { gi = groupIndex.emplace(it.group, (int)pass.groupMasks.size()).first; pass.groupMasks.emplace_back(); pass.groupCutoff.push_back(0.2f); } d.maskGroup = gi->second; }
    pass.items.push_back(d);
  }
  if (!anyMasked) return;
  for (Component* c : reg(CK_MASK)) {
    GameObject* go = liveOwner(c); if (!go || !goActive(go) || !(cam->_mask & (1 << go->_layer))) continue;
    auto* m = static_cast<SpriteMask*>(c);
    {
      if (!m->_enabled || m->_sprite.isNull()) continue;
      engine::DrawItem d; if (!spriteQuad(m->_sprite.get(), m->transform.get(), false, false, ox, oy, left, top, ppu, d)) continue;
      d.r = d.g = d.b = d.a = 1;
      GameObject* grp = sortingGroupOf(go);
      if (grp) { auto gi = groupIndex.find(grp); if (gi == groupIndex.end()) continue; pass.groupMasks[gi->second].push_back(d); pass.groupCutoff[gi->second] = m->_cutoff; }
      else { pass.masks.push_back(d); pass.maskCutoff = m->_cutoff; }
    }
  }
}
static void buildCameraPass(Camera* cam, int W, int H, engine::CameraPass& pass) { auto all = collectRenderers(); buildCameraPassFrom(cam, W, H, pass, all); }
static void preRender(Camera* cam) {
  // Unity sends OnPreRender to scripts on the camera's GameObject (only Scissor uses it)
  if (g.viewer || !cam->gameObject.get()) return;
  auto comps = cam->gameObject->_comps; EventArg none;
  for (auto& c : comps) if (auto* mb = compAs<MonoBehaviour>(c.get())) if (mb->_cls && mb->_cls->invoke && mb->_enabled) guarded(mb, "OnPreRender", [&] { mb->_cls->invoke(mb, "OnPreRender", none); });
}
void engine::buildFrame(std::vector<CameraPass>& out) {
  out.clear();
  auto cams = activeCameras();
  for (Camera* cam : cams) if (!cam->_target.get()) preRender(cam);
  auto all = collectRenderers();
  for (Camera* cam : cams) {
    if (cam->_target.get()) continue;
    CameraPass pass; buildCameraPassFrom(cam, SCREEN_W, SCREEN_H, pass, all);
    out.push_back(std::move(pass));
  }
}

// ======================================================================= main entry points
bool engine::init(const std::string& dataDir, const std::string& saveDir) {
  g.data = dataDir; g.save = saveDir;
  cs::setLogFile((saveDir + "/log.txt").c_str());
  bool ok = loadJson("manifest.json", g.manifest) && loadJson("textures.json", g.textures) && loadJson("sprites.json", g.sprites) &&
            loadJson("audio.json", g.audio) && loadJson("texts.json", g.texts) && loadJson("anims.json", g.anims) &&
            loadJson("controllers.json", g.ctrls) && loadJson("prefabs.json", g.prefabs) && loadJson("resources.json", g.resources) &&
            loadJson("assetindex.json", g.assetIndex);
  if (!ok) return false;
  g.texObjs.resize(g.textures.size()); g.spriteObjs.resize(g.sprites.size()); g.audioObjs.resize(g.audio.size());
  g.textObjs.resize(g.texts.size()); g.prefabObjs.resize(g.prefabs.size()); g.clipObjs.resize(g.anims.size()); g.ctrlObjs.resize(g.ctrls.size());
  const JVal& sl = g.manifest["sortingLayers"]; for (size_t i = 0; i < sl.size(); i++) g.sortingLayerOrder[sl[i]["id"].i()] = (int)i;
  const JVal& ln = g.manifest["layers"]; for (size_t i = 0; i < ln.size(); i++) g.layerNames.push_back(ln[i].str());
  loadPrefs();
  { std::vector<std::string> fm; for (size_t i = 0; i < g.audio.size(); i++) fm.push_back(g.audio[i]["f"].str()); audio::init(g.data, fm); }
  gameStaticInit();
  cs::log("data loaded: %d scenes, %d textures, %d sprites, %d sounds, %d script classes registered",
    (int)g.manifest["scenes"].size(), (int)g.textures.size(), (int)g.sprites.size(), (int)g.audio.size(), (int)classes().size());
  return true;
}
void engine::setInput(const InputState& in) { g.prev = g.in; g.in = in; }
void engine::frame(float dt) {
  if (dt > 1.0f / 3) dt = 1.0f / 3;
  Time::_dt = dt; Time::_time += dt; Time::_frame++;
  profSample = !profClasses && (Time::_frame % 300) == 0; if (profSample) profSampledFrames++;
  profTiming = !profClasses && profArmFrames > 0; if (profArmFrames > 0) profArmFrames--; slowN = 0;
  double t0 = nowMs(), t;
  if (g.pendingScene >= 0) { int s = g.pendingScene; g.pendingScene = -1; loadSceneNow(s); }
  t = nowMs(); profPhase[0] += t - t0; t0 = t;
  if (!g.viewer) {
    sortBehaviours();
    mouseEvents();
    t = nowMs(); profPhase[1] += t - t0; t0 = t;
    auto list = g.behaviours;
    for (auto& mb : list) {
      MonoBehaviour* m = mb.get();
      if (!m || m->_destroyed || m->_pendingDestroy || !m->_cls || !m->_enabled || !m->gameObject.get() || m->gameObject->_pendingDestroy || !goActive(m->gameObject.get())) continue;
      if (!m->_started) { m->_started = true; call(m, m->_cls->Start, "Start"); }
    }
    t = nowMs(); profPhase[2] += t - t0; t0 = t;
    for (auto& mb : list) {
      MonoBehaviour* m = mb.get();
      if (!m || !m->_cls || !m->_cls->Update || m->_destroyed || m->_pendingDestroy || !m->_enabled || !m->_started || !m->gameObject.get() || m->gameObject->_pendingDestroy || !goActive(m->gameObject.get())) continue;
      call(m, m->_cls->Update, "Update");
    }
    t = nowMs(); profPhase[3] += t - t0; t0 = t;
    runTimers();
    t = nowMs(); profPhase[4] += t - t0; t0 = t;
  }
  updateAnimators(dt);
  t = nowMs(); profPhase[5] += t - t0; t0 = t;
  if (!g.viewer) {
    auto list = g.behaviours;
    for (auto& mb : list) {
      MonoBehaviour* m = mb.get();
      if (!m || !m->_cls || !m->_cls->LateUpdate || m->_destroyed || m->_pendingDestroy || !m->_enabled || !m->_started || !m->gameObject.get() || m->gameObject->_pendingDestroy || !goActive(m->gameObject.get())) continue;
      call(m, m->_cls->LateUpdate, "LateUpdate");
    }
  }
  t = nowMs(); profPhase[6] += t - t0; t0 = t;
  flushDestroyed();
  reapVoices();
  if (g.prefsDirty) { g.prefsTimer += dt; if (g.prefsTimer > 10) { g.prefsTimer = 0; savePrefs(); } }
  profPhase[7] += nowMs() - t0; profFrames++;
}
bool engine::quitRequested() { return g.quit; }
void engine::shutdown() { if (g.prefsDirty) savePrefs(); }
int engine::sceneCount() { return (int)g.manifest["scenes"].size(); }
const char* engine::sceneName(int i) { return g.manifest["scenes"][i].str().c_str(); }
void engine::setViewerMode(bool on) { g.viewer = on; }
int engine::scriptErrors() { return g.scriptErrors; }



int gameClassCount() { return (int)classes().size(); }

// Debug: cameras and what they can see
void engineDebugDump() {
  for (Camera* c : activeCameras()) {
    float vx, vy, vw, vh; camView(c, vx, vy, vw, vh);
    cs::log("camera '%s' depth %.1f mask %08x size %.3f pos %.3f,%.3f,%.3f rect %.2f,%.2f,%.2f,%.2f custom %d target %d clear %d",
      c->gameObject->_name.utf8().c_str(), c->_depth, (unsigned)c->_mask, c->_size, c->transform->get_position().x, c->transform->get_position().y, c->transform->get_position().z,
      c->_rect.x, c->_rect.y, c->_rect.width, c->_rect.height, (int)c->_customProj, c->_target.get() ? 1 : 0, (int)c->_clear);
  }
  std::map<int, int> perLayer; std::map<int, std::string> sample;
  for (auto& go : g.objects) {
    if (go.isNull() || go->_scene == -3 || !goActive(go.get())) continue;
    for (auto& c : go->_comps) if (auto* sr = compAs<SpriteRenderer>(c.get())) if (sr->_enabled && sr->_sprite.get()) {
      perLayer[go->_layer]++;
      if (sample[go->_layer].size() < 160) { Vector3 p = go->transform->get_position(); char b[96]; snprintf(b, sizeof b, " %s(%.2f,%.2f,%.2f a%.2f)", go->_name.utf8().c_str(), p.x, p.y, p.z, sr->_color.a); sample[go->_layer] += b; }
    }
  }
  for (auto& kv : perLayer) cs::log("layer %d (%s): %d sprites:%s", kv.first, kv.first < (int)g.layerNames.size() ? g.layerNames[kv.first].c_str() : "?", kv.second, sample[kv.first].c_str());
}
