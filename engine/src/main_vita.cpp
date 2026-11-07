// PS Vita entry point: vitaGL renderer (on its own thread), controls, main loop.
// Controls: touch = tap to click, right stick = move cursor (left stick if chosen in Options), X = click, O = right click (look),
//           Triangle = inventory (I), Square = journal (J), Start = menu (Esc).
// Viewer mode (no scripts yet): L / R = previous / next scene.
#include "engine.h"
#include <vitaGL.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/io/stat.h>
#include <psp2/power.h>
#include <psp2/apputil.h>
#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/cpu.h>
#include <map>
#include <set>
#include <malloc.h>
#include <vector>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>

extern "C" { unsigned int _newlib_heap_size_user = 220 * 1024 * 1024; }
int gameClassCount();
namespace cs { void setLogFile(const char* path); }
int engineTakeProfile(double out[8], const char* names[8]);
int engineTopScripts(char* out, int n);
void engineArmCallTiming(int frames);
bool engineFrameWasSampled();
bool engineSlowCalls(char* out, int n);

static const char* ROOT = "ux0:data/DontEscape";
static volatile bool audioRunning = true;
static int audioThread(SceSize, void*) {
  int port = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM, 1024, 48000, SCE_AUDIO_OUT_MODE_STEREO);
  if (port < 0) return 0;
  int vol[2] = { SCE_AUDIO_VOLUME_0DB, SCE_AUDIO_VOLUME_0DB };
  sceAudioOutSetVolume(port, (SceAudioOutChannelFlag)(SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH), vol);
  static int16_t buf[2][1024 * 2]; int k = 0;
  while (audioRunning) { engine::mixAudio(buf[k], 1024, 48000); sceAudioOutOutput(port, buf[k]); k ^= 1; }
  sceAudioOutReleasePort(port);
  return 0;
}
static const int OY = 2; // 960x540 game area centred on the 544-pixel screen

struct Tex { GLuint id; int lastUsed; size_t bytes; };
static std::map<int, Tex> texCache;
static std::map<int, int> texRetryAt, texFails;   // textures that failed to load: frame to try again, failure count
static size_t texBytes = 0;
static std::map<const Texture2D*, GLuint> runtimeTex;
static int frameNo = 0;      // game thread: frames built
static int rFrame = 0;       // render thread: frame being drawn (texture use / eviction ages)
static int texUploads = 0;   // render thread: textures uploaded this frame (loading new art: such frames are not typical)

// The render thread must not call cs::log (not thread-safe): its lines are queued and written by the game thread.
static SceKernelLwMutexWork rlogLock; static bool rlogReady = false; static std::vector<std::string> rlogQueue;
static void rlog(const char* fmt, ...) {
  char b[512]; va_list ap; va_start(ap, fmt); vsnprintf(b, sizeof b, fmt, ap); va_end(ap);
  if (!rlogReady) { cs::log("%s", b); return; }
  sceKernelLockLwMutex(&rlogLock, 1, nullptr); rlogQueue.push_back(b); sceKernelUnlockLwMutex(&rlogLock, 1);
}
static void rlogFlush() {
  if (!rlogReady) return;
  std::vector<std::string> q;
  sceKernelLockLwMutex(&rlogLock, 1, nullptr); q.swap(rlogQueue); sceKernelUnlockLwMutex(&rlogLock, 1);
  for (auto& l : q) cs::log("%s", l.c_str());
}

static void logMem(const char* why) {
  rlog("[vita] %s: %d textures (%.1f MB); free VRAM %.1f MB, RAM %.1f MB, PHYCONT %.1f MB", why, (int)texCache.size(), texBytes / 1048576.0,
          vglMemFree(VGL_MEM_VRAM) / 1048576.0, vglMemFree(VGL_MEM_RAM) / 1048576.0, vglMemFree(VGL_MEM_PHYCONT) / 1048576.0);
}
// free textures not drawn since frame `since`
static int evictUnused(int since) {
  int n = 0;
  for (auto it = texCache.begin(); it != texCache.end();) {
    if (it->second.lastUsed < since) { glDeleteTextures(1, &it->second.id); texBytes -= it->second.bytes; it = texCache.erase(it); n++; }
    else ++it;
  }
  return n;
}
// Textures are uploaded with premultiplied alpha, so normal, multiply and additive sprites all blend right
// (including half-transparent edges): see setBlend().
static void premultiply(std::vector<uint8_t>& px) {
  for (size_t i = 0; i + 3 < px.size(); i += 4) { unsigned a = px[i + 3]; if (a == 255) continue; px[i] = (uint8_t)(px[i] * a / 255); px[i + 1] = (uint8_t)(px[i + 1] * a / 255); px[i + 2] = (uint8_t)(px[i + 2] * a / 255); }
}
static void setBlend(int mode) {
  if (mode == 1) glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);   // multiply: dst * lerp(1, src, alpha)
  else if (mode == 2) glBlendFunc(GL_ONE, GL_ONE);                     // additive light
  else glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);                    // normal (premultiplied)
}
static bool uploadRGBA(int w, int h, const std::vector<uint8_t>& px) {
  while (glGetError() != GL_NO_ERROR) {}
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, px.data());
  return glGetError() == GL_NO_ERROR;
}

static GLuint textureFor(const engine::DrawItem& d) {
  if (d.rtex) {   // runtime texture (save thumbnails): uploaded by uploadRuntime() from the frame packet
    auto it = runtimeTex.find(d.rtex); if (it == runtimeTex.end()) return 0;
    glBindTexture(GL_TEXTURE_2D, it->second); return it->second;
  }
  auto it = texCache.find(d.tex);
  if (it != texCache.end()) { it->second.lastUsed = rFrame; glBindTexture(GL_TEXTURE_2D, it->second.id); return it->second.id; }
  // A texture that failed recently is skipped until its retry frame (0 = draw nothing).
  auto rf = texRetryAt.find(d.tex);
  if (rf != texRetryAt.end() && rFrame < rf->second) return 0;
  std::vector<uint8_t> px; int w = 0, h = 0; const char* why = "";
  if (!engine::loadTexturePixels(d.tex, px, w, h, &why)) {
    int tries = ++texFails[d.tex];
    rlog("[vita] texture %d (%s) failed to load: %s (attempt %d)", d.tex, engine::textureName(d.tex), why, tries);
    texRetryAt[d.tex] = rFrame + (tries < 3 ? 30 : 600);
    return 0;
  }
  premultiply(px);
  GLuint id; glGenTextures(1, &id); glBindTexture(GL_TEXTURE_2D, id);
  if (!uploadRGBA(w, h, px)) {
    // most likely out of GPU memory: free all art not drawn this frame and try once more
    logMem("texture upload failed");
    int freed = evictUnused(rFrame);
    glBindTexture(GL_TEXTURE_2D, id);
    if (!uploadRGBA(w, h, px)) {
      rlog("[vita] texture %d (%s) %dx%d could not be uploaded (freed %d others first)", d.tex, engine::textureName(d.tex), w, h, freed);
      glDeleteTextures(1, &id); texRetryAt[d.tex] = rFrame + 30; ++texFails[d.tex];
      return 0;
    }
    rlog("[vita] texture %d (%s) uploaded after freeing %d others", d.tex, engine::textureName(d.tex), freed);
  }
  if (texFails.count(d.tex)) { rlog("[vita] texture %d (%s) loaded on retry", d.tex, engine::textureName(d.tex)); texFails.erase(d.tex); texRetryAt.erase(d.tex); }
  GLint f = engine::textureFilter(d.tex) ? GL_LINEAR : GL_NEAREST;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  size_t bytes = (size_t)w * h * 4;
  texCache[d.tex] = { id, rFrame, bytes }; texBytes += bytes; texUploads++;
  return id;
}
static void evictTextures() { evictUnused(rFrame - 180); }   // free textures not drawn for 3 seconds

static std::vector<float> verts, uvs, cols;
static int drawCalls = 0;
static void flush() {
  if (verts.empty()) return;
  drawCalls++;
  glVertexPointer(2, GL_FLOAT, 0, verts.data()); glTexCoordPointer(2, GL_FLOAT, 0, uvs.data()); glColorPointer(4, GL_FLOAT, 0, cols.data());
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(verts.size() / 2));
  verts.clear(); uvs.clear(); cols.clear();
}
static void quad(const engine::DrawItem& d) {
  float x0 = d.x0, x1 = d.x1, y0 = d.y0 + OY, y1 = d.y1 + OY;
  float v[12] = { x0, y0, x1, y0, x1, y1, x0, y0, x1, y1, x0, y1 };
  float t[12] = { d.u0, d.v0, d.u1, d.v0, d.u1, d.v1, d.u0, d.v0, d.u1, d.v1, d.u0, d.v1 };
  verts.insert(verts.end(), v, v + 12); uvs.insert(uvs.end(), t, t + 12);
  for (int i = 0; i < 6; i++) { cols.push_back(d.r * d.a); cols.push_back(d.g * d.a); cols.push_back(d.b * d.a); cols.push_back(d.a); }   // premultiplied
}
static void renderFrame(const std::vector<engine::CameraPass>& passes) {
  glViewport(0, 0, 960, 544);
  glDisable(GL_SCISSOR_TEST);
  glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION); glLoadIdentity(); glOrtho(0, 960, 544, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
  glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND); setBlend(0);
  glEnableClientState(GL_VERTEX_ARRAY); glEnableClientState(GL_TEXTURE_COORD_ARRAY); glEnableClientState(GL_COLOR_ARRAY);
  for (auto& p : passes) {
    glEnable(GL_SCISSOR_TEST); glScissor(p.vx, 544 - (p.vy + OY + p.vh), p.vw, p.vh);
    if (p.clear) { glClearColor(p.bg[0], p.bg[1], p.bg[2], 1); glClear(GL_COLOR_BUFFER_BIT); }
    // Sprite masks via stencil. Ungrouped masks use stencil value 1; each SortingGroup gets its own value,
    // written just before its (contiguous) items are drawn.
    bool stencilUsed = !p.masks.empty() || !p.groupMasks.empty();
    if (stencilUsed) { glEnable(GL_STENCIL_TEST); glClearStencil(0); glClear(GL_STENCIL_BUFFER_BIT); glDisable(GL_STENCIL_TEST); }
    auto writeMasks = [&](const std::vector<engine::DrawItem>& masks, float cutoff, int ref) {
      flush();
      glEnable(GL_STENCIL_TEST); glStencilFunc(GL_ALWAYS, ref, 0xFF); glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); glEnable(GL_ALPHA_TEST); glAlphaFunc(GL_GREATER, cutoff);
      for (auto& m : masks) { if (textureFor(m)) { quad(m); flush(); } }
      glDisable(GL_ALPHA_TEST); glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    };
    if (!p.masks.empty()) writeMasks(p.masks, p.maskCutoff, 1);
    int mode = 0, curGroup = -2, nextRef = 2, curRef = 1, curBlend = 0;
    GLuint bound = 0;
    for (auto& d : p.items) {
      if (d.blend != curBlend) { flush(); curBlend = d.blend; setBlend(curBlend); }
      int grp = d.maskMode ? d.maskGroup : -2;
      if (d.maskMode != mode || grp != curGroup) {
        flush(); bound = 0;
        if (d.maskMode && d.maskGroup >= 0 && grp != curGroup) {
          if (nextRef > 255) { glClear(GL_STENCIL_BUFFER_BIT); nextRef = 2; if (!p.masks.empty()) writeMasks(p.masks, p.maskCutoff, 1); }
          curRef = nextRef++; writeMasks(p.groupMasks[d.maskGroup], p.groupCutoff[d.maskGroup], curRef);
        } else if (d.maskMode && d.maskGroup < 0) curRef = 1;
        mode = d.maskMode; curGroup = grp;
        if (!mode) glDisable(GL_STENCIL_TEST);
        else { glEnable(GL_STENCIL_TEST); glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); glStencilFunc(mode == 1 ? GL_EQUAL : GL_NOTEQUAL, curRef, 0xFF); }
      }
      GLuint id = d.rtex ? 0 : (texCache.count(d.tex) ? texCache[d.tex].id : 0);
      if (!id || id != bound) { flush(); id = textureFor(d); bound = id; }
      else texCache[d.tex].lastUsed = rFrame;
      if (!id) continue;   // texture not available (failed to load): skip it rather than draw with nothing bound
      quad(d);
    }
    flush();
    if (curBlend) setBlend(0);
    glDisable(GL_STENCIL_TEST);
  }
  glDisable(GL_SCISSOR_TEST);
}

// Stick value (-128..127 around the centre) to cursor speed: dead zone 24, then linear up to full speed.
static float stickAxis(int v) {
  const int DZ = 24;
  if (v > DZ) return (v - DZ) / (127.0f - DZ);
  if (v < -DZ) return (v + DZ) / (128.0f - DZ);
  return 0;
}

static void readInput(engine::InputState& in, bool viewer, int& sceneDelta, float dt) {
  static SceCtrlData prev; SceCtrlData pad; sceCtrlPeekBufferPositive(0, &pad, 1);
  SceTouchData touch; sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
  auto pressed = [&](unsigned b) { return (pad.buttons & b) && !(prev.buttons & b); };
  // The right stick moves the cursor; Options > "Cursor" switches it to the left stick (pref cursorStick = 1).
  // Speeds are per second so the cursor feels the same whatever the frame rate.
  if (dt > 0.1f) dt = 0.1f;
  bool leftStick = PlayerPrefs::GetInt(String("cursorStick"), 0) == 1;
  int sx = (leftStick ? pad.lx : pad.rx) - 128, sy = (leftStick ? pad.ly : pad.ry) - 128;
  const float STICK_SPEED = 480.0f, DPAD_SPEED = 180.0f;   // pixels per second at full tilt
  in.mouseX += stickAxis(sx) * STICK_SPEED * dt;
  in.mouseY -= stickAxis(sy) * STICK_SPEED * dt;
  if (pad.buttons & SCE_CTRL_LEFT) in.mouseX -= DPAD_SPEED * dt; if (pad.buttons & SCE_CTRL_RIGHT) in.mouseX += DPAD_SPEED * dt;
  if (pad.buttons & SCE_CTRL_UP) in.mouseY += DPAD_SPEED * dt; if (pad.buttons & SCE_CTRL_DOWN) in.mouseY -= DPAD_SPEED * dt;
  bool touching = touch.reportNum > 0;
  if (touching) { in.mouseX = touch.report[0].x / 2.0f; in.mouseY = engine::SCREEN_H - (touch.report[0].y / 2.0f - OY); }
  if (in.mouseX < 0) in.mouseX = 0; if (in.mouseX > engine::SCREEN_W - 1) in.mouseX = engine::SCREEN_W - 1;
  if (in.mouseY < 0) in.mouseY = 0; if (in.mouseY > engine::SCREEN_H - 1) in.mouseY = engine::SCREEN_H - 1;
  in.mouse[0] = touching || (pad.buttons & SCE_CTRL_CROSS);
  in.mouse[1] = (pad.buttons & SCE_CTRL_CIRCLE) != 0;
  in.keys[(int)KeyCode::Escape] = (pad.buttons & SCE_CTRL_START) != 0;
  in.keys[(int)KeyCode::I] = (pad.buttons & SCE_CTRL_TRIANGLE) != 0;
  in.keys[(int)KeyCode::J] = (pad.buttons & SCE_CTRL_SQUARE) != 0;
  in.keys[(int)KeyCode::Space] = (pad.buttons & SCE_CTRL_SELECT) != 0;
  sceneDelta = 0;
  if (viewer) { if (pressed(SCE_CTRL_LTRIGGER)) sceneDelta = -1; if (pressed(SCE_CTRL_RTRIGGER)) sceneDelta = 1; }
  prev = pad;
}

// ---- one-time data check: compares every data file on the card with data/checksums.txt (tools/checksums.js)
static uint32_t crcTable[256];
static uint32_t crcUpdate(uint32_t c, const uint8_t* p, size_t n) { while (n--) c = crcTable[(c ^ *p++) & 0xFF] ^ (c >> 8); return c; }
static void progressBar(float t) {
  glDisable(GL_SCISSOR_TEST); glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_SCISSOR_TEST);
  glScissor(280, 268, 400, 8); glClearColor(0.25f, 0.25f, 0.25f, 1); glClear(GL_COLOR_BUFFER_BIT);
  int w = (int)(400 * t); if (w > 0) { glScissor(280, 268, w, 8); glClearColor(0.85f, 0.85f, 0.85f, 1); glClear(GL_COLOR_BUFFER_BIT); }
  glDisable(GL_SCISSOR_TEST); vglSwapBuffers(GL_FALSE);
}
static void checkData(const std::string& data, const std::string& save) {
  for (uint32_t n = 0; n < 256; n++) { uint32_t c = n; for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1; crcTable[n] = c; }
  std::string list;
  { FILE* f = fopen((data + "/checksums.txt").c_str(), "rb"); if (!f) { cs::log("[datacheck] no checksums.txt, skipped"); return; }
    char b[65536]; size_t n; while ((n = fread(b, 1, sizeof b, f)) > 0) list.append(b, n); fclose(f); }
  char listId[16]; snprintf(listId, sizeof listId, "%08x", (unsigned)(crcUpdate(crcUpdate(0xFFFFFFFFu, (const uint8_t*)list.data(), list.size()), (const uint8_t*)data.data(), data.size()) ^ 0xFFFFFFFFu));   // list + data location
  std::string marker = save + "/datacheck_ok.txt";
  { FILE* f = fopen(marker.c_str(), "rb"); if (f) { char m[16] = {}; fread(m, 1, 8, f); fclose(f); if (!strcmp(m, listId)) return; } }
  cs::setLogFile((save + "/datacheck_log.txt").c_str());   // kept apart: log.txt is rewritten every launch
  std::vector<std::string> lines; size_t p = 0;
  while (p < list.size()) { size_t e = list.find('\n', p); if (e == std::string::npos) e = list.size(); if (e > p) lines.push_back(list.substr(p, e - p)); p = e + 1; }
  static uint8_t buf[256 * 1024]; int bad = 0;
  for (size_t i = 0; i < lines.size(); i++) {
    unsigned want = 0; unsigned long size = 0; char rel[512] = {};
    if (sscanf(lines[i].c_str(), "%x %lu %511[^\n]", &want, &size, rel) != 3) continue;
    FILE* f = fopen((data + "/" + rel).c_str(), "rb");
    if (!f) { cs::log("[datacheck] missing: %s", rel); bad++; continue; }
    uint32_t c = 0xFFFFFFFFu; unsigned long got = 0; size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) { c = crcUpdate(c, buf, n); got += n; }
    fclose(f); c ^= 0xFFFFFFFFu;
    if (got != size || c != want) { cs::log("[datacheck] damaged: %s (size %lu, expected %lu)", rel, got, size); bad++; }
    if ((i & 63) == 0) progressBar((float)i / lines.size());
  }
  cs::log("[datacheck] %d of %d files checked, %d damaged or missing", (int)lines.size(), (int)lines.size(), bad);
  if (!bad) { FILE* f = fopen(marker.c_str(), "wb"); if (f) { fputs(listId, f); fclose(f); } }
}

// ---- render thread ------------------------------------------------------------------------------------------
// The game thread builds a frame's draw lists into a FramePacket and hands it over; the render thread turns it into
// GPU commands and presents it while the game thread already runs the next frame (one frame in flight). After
// start-up every GL call happens on the render thread.
struct RtUpload { const Texture2D* t; int w, h; std::vector<uint8_t> px; };
struct FramePacket {
  std::vector<engine::CameraPass> passes;
  std::vector<P<Texture2D>> keep;   // runtime textures drawn in this frame, kept alive until the packet is reused
  std::vector<RtUpload> uploads;    // runtime textures whose pixels changed, copied on the game thread
  int frame = 0, sceneFirstFrame = -1000, swapInterval = 1; bool quit = false;
  // filled in by the render thread
  unsigned renderUs = 0, swapUs = 0; int draws = 0, uploadsDone = 0;
};
static FramePacket packets[2];
static SceUID semWork = -1, semDone = -1;
static volatile int workIdx = 0;
static std::set<const Texture2D*> rtexKnown;   // game thread: runtime textures the renderer has been given

static void uploadRuntime(RtUpload& u) {
  GLuint& id = runtimeTex[u.t]; if (!id) glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  premultiply(u.px);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u.w, u.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, u.px.data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
// draws one packet and presents it (render thread, or the game thread when single_thread.txt is on the card)
static int swapIntervalNow = 1;
static void renderPacket(FramePacket& p) {
    rFrame = p.frame;
    if (p.swapInterval != swapIntervalNow) { swapIntervalNow = p.swapInterval; eglSwapInterval(EGL_NO_DISPLAY, swapIntervalNow); }
    SceUInt64 a = sceKernelGetProcessTimeWide();
    for (auto& u : p.uploads) uploadRuntime(u);
    drawCalls = 0; texUploads = 0;
    renderFrame(p.passes);
    // A few frames into a new scene, free the previous scene's art so the two never have to fit together for long.
    if (rFrame == p.sceneFirstFrame + 3) { int n = evictUnused(p.sceneFirstFrame); char b[64]; snprintf(b, sizeof b, "scene art loaded (freed %d old)", n); logMem(b); }
    if ((rFrame % 60) == 0) evictTextures();
    SceUInt64 b = sceKernelGetProcessTimeWide();
    vglSwapBuffers(GL_FALSE);
    SceUInt64 c = sceKernelGetProcessTimeWide();
    p.renderUs = (unsigned)(b - a); p.swapUs = (unsigned)(c - b); p.draws = drawCalls; p.uploadsDone = texUploads;
}
static int renderThread(SceSize, void*) {
  for (;;) {
    sceKernelWaitSema(semWork, 1, NULL);
    FramePacket& p = packets[workIdx];
    if (p.quit) { sceKernelSignalSema(semDone, 1); break; }
    renderPacket(p);
    sceKernelSignalSema(semDone, 1);
  }
  return 0;
}
// game thread: runtime textures a packet draws stay alive with it; changed pixels travel as a copy
static void noteRuntime(FramePacket& pk, Texture2D* t) {
  for (auto& k : pk.keep) if (k.get() == t) return;
  pk.keep.push_back(P<Texture2D>(t));
  if (t->_dirty || !rtexKnown.count(t)) {
    if (!t->_pixels.empty()) pk.uploads.push_back({ t, t->_w, t->_h, std::vector<uint8_t>(t->_pixels.begin(), t->_pixels.end()) });
    t->_dirty = false; rtexKnown.insert(t);
  }
}

int main() {
  scePowerSetArmClockFrequency(444); scePowerSetBusClockFrequency(222); scePowerSetGpuClockFrequency(222); scePowerSetGpuXbarClockFrequency(166);
  SceAppUtilInitParam ip = {}; SceAppUtilBootParam bp = {}; sceAppUtilInit(&ip, &bp);
  sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
  sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
  sceIoMkdir(ROOT, 0777);
  std::string save = std::string(ROOT) + "/save"; sceIoMkdir(save.c_str(), 0777);
  // Cores: game on 0, audio on 1, rendering + vitaGL's garbage collector + sound file loading on 2.
  sceKernelChangeThreadCpuAffinityMask(sceKernelGetThreadId(), SCE_KERNEL_CPU_MASK_USER_0);
  vglSetupGarbageCollector(0x10000100, SCE_KERNEL_CPU_MASK_USER_2);
  vglInit(0x100000);
  bool hasScripts = false;
  hasScripts = gameClassCount() > 0;
  engine::setViewerMode(!hasScripts);
  // Game data: inside the installed app (the release VPK carries it), else the older separate copy on the card.
  std::string dataDir = std::string(ROOT) + "/data";
  { FILE* f = fopen("app0:data/manifest.json", "rb"); if (f) { fclose(f); dataDir = "app0:data"; } }
  checkData(dataDir, save);
  if (!engine::init(dataDir, save)) {
    // no data: red screen for a few seconds
    for (int i = 0; i < 300; i++) { glClearColor(0.5f, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT); vglSwapBuffers(GL_FALSE); }
    sceKernelExitProcess(0); return 0;
  }
  SceUID at = sceKernelCreateThread("audio", audioThread, 0x10000100, 0x10000, 0, SCE_KERNEL_CPU_MASK_USER_1, NULL);
  if (at >= 0) sceKernelStartThread(at, 0, NULL);
  logMem("start");
  cs::log("[vita] game data: %s", dataDir.c_str());
  { SceUInt64 a = sceKernelGetProcessTimeWide(); volatile SceUInt64 x = 0; for (int i = 0; i < 1000; i++) x += sceKernelGetProcessTimeWide(); SceUInt64 b = sceKernelGetProcessTimeWide();
    cs::log("[vita] one clock read takes %.2f us", (b - a) / 1000.0); }
  // From here on only the render thread touches the GPU. Fallback: single_thread.txt on the card draws on this thread.
  bool threaded = true;
  { FILE* f = fopen((std::string(ROOT) + "/single_thread.txt").c_str(), "rb"); if (f) { fclose(f); threaded = false; } }
  if (threaded) {
    sceKernelCreateLwMutex(&rlogLock, "rlog", 0, 0, nullptr); rlogReady = true;
    semWork = sceKernelCreateSema("frame_work", 0, 0, 1, NULL);
    semDone = sceKernelCreateSema("frame_done", 0, 1, 1, NULL);
    SceUID rt = sceKernelCreateThread("render", renderThread, 0x10000100, 0x40000, 0, SCE_KERNEL_CPU_MASK_USER_2, NULL);
    if (semWork < 0 || semDone < 0 || rt < 0 || sceKernelStartThread(rt, 0, NULL) < 0) { threaded = false; rlogReady = false; }
  }
  cs::log("[vita] rendering on %s", threaded ? "its own thread" : "the game thread (single_thread.txt or thread start failed)");
  int scene = hasScripts ? 0 : 1;
  engine::loadSceneNow(scene);
  engine::InputState in;
  SceUInt64 last = sceKernelGetProcessTimeWide();
  int seenSceneLoads = -1, sceneFirstFrame = -1000;
  auto us = [] { return sceKernelGetProcessTimeWide(); };
  // [perf] line in log.txt every 5 seconds. Frames just after an area change (art, Start(), sound loading) and
  // frames that uploaded new art are "settling": left out of the averages and of the pacing decision.
  // A frame costs the slower of the game thread (game + sprites) and the render thread (draw), which now overlap.
  const int SETTLE_FRAMES = 120;
  double pGame = 0, pBuild = 0, pDraw = 0, pSwap = 0, pWait = 0, pWork = 0, pPh[8] = {}; int pFrames = 0, pAll = 0, pDraws = 0, pSlow = 0; unsigned pWorst = 0; SceUInt64 pStart = last;
  const char* phaseNames[8] = {};
  // Pacing: each area starts at 60 fps. If 15% of 2 seconds of settled frames take over 15.5 ms, lock to a steady 30
  // (swap every second refresh) rather than a rate wobbling between 30 and 60. Back to 60 when 95% of the last
  // 120 settled frames are under 13 ms.
  const int PACE_N = 180; static unsigned paceHist[PACE_N]; int paceCount = 0, paceMode = 1, paceSince = 0;   // paceMode 1 = 60 fps, 2 = locked 30
  int k = 0;   // packet the game thread fills next
  int lastHitchLog = -1000;
  engineArmCallTiming(1800);   // time script calls for the first 30 s too: the menu and continuing a save come before any hitch
  while (!engine::quitRequested()) {
    SceUInt64 now = sceKernelGetProcessTimeWide(); float dt = (now - last) / 1000000.0f; last = now;
    int delta; readInput(in, !hasScripts, delta, dt);
    if (delta) { scene = (scene + delta + engine::sceneCount()) % engine::sceneCount(); engine::loadSceneNow(scene); }
    engine::setInput(in);
    SceUInt64 t0 = us();
    engine::frame(dt);
    SceUInt64 t1 = us();
    double fph[8]; engineTakeProfile(fph, phaseNames);   // this frame's game phases (ms)
    FramePacket& pk = packets[k];   // the render thread finished it before the previous handover returned
    pk.keep.clear(); pk.uploads.clear();
    engine::buildFrame(pk.passes);
    for (auto& pass : pk.passes) {
      for (auto& d : pass.items) if (d.rtex) noteRuntime(pk, d.rtex);
      for (auto& d : pass.masks) if (d.rtex) noteRuntime(pk, d.rtex);
      for (auto& gm : pass.groupMasks) for (auto& d : gm) if (d.rtex) noteRuntime(pk, d.rtex);
    }
    frameNo++;
    if (engine::sceneLoadCount() != seenSceneLoads) {
      seenSceneLoads = engine::sceneLoadCount(); sceneFirstFrame = frameNo; paceCount = 0;
      paceMode = 1;   // every area gets its chance at 60
    }
    if (frameNo == sceneFirstFrame + SETTLE_FRAMES) { char junk[512]; engineTopScripts(junk, sizeof junk); }   // drop the loading frames' script timings
    pk.frame = frameNo; pk.sceneFirstFrame = sceneFirstFrame; pk.swapInterval = paceMode == 1 ? 1 : 2; pk.quit = false;
    SceUInt64 t2 = us();
    unsigned renderUs, swapUs; int draws, uploads; SceUInt64 t3;
    if (threaded) {
      // hand the frame over once the render thread has finished the previous one
      sceKernelWaitSema(semDone, 1, NULL);
      t3 = us();
      const FramePacket& prev = packets[k ^ 1];   // the frame the render thread just finished
      renderUs = prev.renderUs; swapUs = prev.swapUs; draws = prev.draws; uploads = prev.uploadsDone;
      workIdx = k; sceKernelSignalSema(semWork, 1);
      rlogFlush();
    } else {
      t3 = us();
      renderPacket(pk);
      renderUs = pk.renderUs; swapUs = pk.swapUs; draws = pk.draws; uploads = pk.uploadsDone;
    }
    k ^= 1;
    unsigned mainUs = (unsigned)(t2 - t0);
    unsigned work = mainUs > renderUs ? mainUs : renderUs;   // the slower of the two threads sets the pace
    // the 1-in-300 frame that times every script for the top list runs slower: not typical either
    bool settling = frameNo < sceneFirstFrame + SETTLE_FRAMES || uploads > 0 || engineFrameWasSampled();
    pAll++;
    if (!settling) {
      pFrames++; pGame += t1 - t0; pBuild += t2 - t1; pDraw += renderUs; pSwap += swapUs; pWait += t3 - t2; pWork += work; pDraws += draws;
      for (int i = 0; i < 8; i++) pPh[i] += fph[i];
      if (work > pWorst) pWorst = work; if (work > 15500) pSlow++;
      // A settled frame over 18 ms shows as a stutter: log what it spent its time on. Script calls are then timed
      // one by one for 10 seconds, so the next hitch (they tend to repeat) names the scripts that caused it.
      if (work > 18000 && frameNo - lastHitchLog >= 20) {
        char calls[320]; bool timed = engineSlowCalls(calls, sizeof calls);
        cs::log("[hitch] frame %d: %.1f ms | game thread %.1f ms (%s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, sprites %.1f) | render thread %.1f ms, %d new textures | slowest scripts: %s",
                frameNo, work / 1000.0, mainUs / 1000.0, phaseNames[0], fph[0], phaseNames[1], fph[1], phaseNames[2], fph[2], phaseNames[3], fph[3],
                phaseNames[4], fph[4], phaseNames[5], fph[5], phaseNames[6], fph[6], phaseNames[7], fph[7], (t2 - t1) / 1000.0, renderUs / 1000.0, uploads,
                timed ? calls : "not timed yet (now timing every script call for 10 s)");
        lastHitchLog = frameNo;
        engineArmCallTiming(600);
      }
      paceHist[paceCount % PACE_N] = work; paceCount++;
      if (paceCount >= 120) {
        if (paceMode == 1) {
          int slow = 0; for (int i = 1; i <= 120; i++) if (paceHist[(paceCount - i) % PACE_N] > 15500) slow++;
          if (slow >= 18) { paceMode = 2; paceSince = paceCount; cs::log("[pace] locked to 30 fps (%d of the last 120 frames took over 15.5 ms)", slow); }
        } else if (paceCount - paceSince >= 120) {
          int slow = 0; for (int i = 1; i <= 120; i++) if (paceHist[(paceCount - i) % PACE_N] > 13000) slow++;
          if (slow <= 6) { paceMode = 1; paceSince = paceCount; cs::log("[pace] back to 60 fps (%d of the last 120 frames over 13 ms)", slow); }
        }
      }
    }
    SceUInt64 t4 = us();
    if (t4 - pStart >= 5000000) {
      double secs = (t4 - pStart) / 1e6, f = pFrames ? pFrames : 1;
      char top[512]; engineTopScripts(top, sizeof top);
      struct mallinfo mi = mallinfo();   // heap: 220 MB (_newlib_heap_size_user)
      cs::log("[heap] %.1f MB in use, %.1f MB taken from the 220 MB heap", mi.uordblks / 1048576.0, mi.arena / 1048576.0);
      if (pFrames)
        cs::log("[perf] %.1f fps (target %d), %d of %d frames settled | frame %.1f ms avg, %.1f worst, %d over 15.5 | game thread %.1f ms: game %.1f (%s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f, %s %.1f), sprites %.1f, waiting %.1f | render thread %.1f ms, %.0f draws, swap/vsync %.1f | top scripts: %s",
                pAll / secs, paceMode == 1 ? 60 : 30, pFrames, pAll, pWork / f / 1000, pWorst / 1000.0, pSlow, (pGame + pBuild) / f / 1000, pGame / f / 1000,
                phaseNames[0], pPh[0] / f, phaseNames[1], pPh[1] / f, phaseNames[2], pPh[2] / f, phaseNames[3], pPh[3] / f, phaseNames[4], pPh[4] / f, phaseNames[5], pPh[5] / f, phaseNames[6], pPh[6] / f, phaseNames[7], pPh[7] / f,
                pBuild / f / 1000, pWait / f / 1000, pDraw / f / 1000, pDraws / f, pSwap / f / 1000, top);
      else cs::log("[perf] %.1f fps (target %d), loading (no settled frames)", pAll / secs, paceMode == 1 ? 60 : 30);
      pGame = pBuild = pDraw = pSwap = pWait = pWork = 0; for (double& x : pPh) x = 0; pFrames = pAll = pDraws = pSlow = 0; pWorst = 0; pStart = t4;
    }
  }
  if (threaded) {   // stop the render thread after its last frame
    sceKernelWaitSema(semDone, 1, NULL);
    packets[k].quit = true; workIdx = k; sceKernelSignalSema(semWork, 1);
    sceKernelWaitSema(semDone, 1, NULL);
    rlogFlush();
  }
  audioRunning = false;
  engine::shutdown();
  cs::logFlush();
  sceKernelExitProcess(0);
  return 0;
}
