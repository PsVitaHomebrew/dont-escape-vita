// PC test runner: runs the engine headless and writes screenshots (PNG) with a software renderer.
// Usage: detest <dataDir> <saveDir> <scene> <frames> <out.png> [--viewer] [--click x,y@frame ...] [--key code@frame]
#include "engine.h"
#include "inflate.h"
#include "audio.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <direct.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

static std::map<int, std::vector<uint8_t>> texCache; static std::map<int, std::pair<int, int>> texSize;
static const std::vector<uint8_t>* tex(int i, int& w, int& h) {
  auto it = texCache.find(i);
  if (it == texCache.end()) { std::vector<uint8_t> px; int tw = 0, th = 0; engine::loadTexturePixels(i, px, tw, th); texSize[i] = { tw, th }; it = texCache.emplace(i, std::move(px)).first; }
  w = texSize[i].first; h = texSize[i].second; return &it->second;
}

static void render(const std::vector<engine::CameraPass>& passes, std::vector<uint8_t>& fb, int W, int H) {
  fb.assign((size_t)W * H * 4, 0); for (size_t i = 3; i < fb.size(); i += 4) fb[i] = 255;
  for (auto& p : passes) {
    if (p.clear) for (int y = p.vy; y < p.vy + p.vh; y++) for (int x = p.vx; x < p.vx + p.vw; x++) {
      if (x < 0 || y < 0 || x >= W || y >= H) continue; uint8_t* d = &fb[((size_t)y * W + x) * 4];
      d[0] = (uint8_t)(p.bg[0] * 255); d[1] = (uint8_t)(p.bg[1] * 255); d[2] = (uint8_t)(p.bg[2] * 255);
    }
    for (auto& it : p.items) {
      int tw, th; const std::vector<uint8_t>* t = nullptr; const uint8_t* src = nullptr;
      if (it.rtex) { tw = it.rtex->_w; th = it.rtex->_h; src = it.rtex->_pixels.data(); }
      else { t = tex(it.tex, tw, th); src = t->data(); }
      if (!src || tw <= 0 || th <= 0) continue;
      int x0 = (int)std::floor(it.x0 + 0.5f), x1 = (int)std::floor(it.x1 + 0.5f), y0 = (int)std::floor(it.y0 + 0.5f), y1 = (int)std::floor(it.y1 + 0.5f);
      float dw = it.x1 - it.x0, dh = it.y1 - it.y0; if (dw <= 0 || dh <= 0) continue;
      for (int y = std::max(y0, p.vy); y < std::min(y1, p.vy + p.vh); y++) {
        if (y < 0 || y >= H) continue;
        float fy = ((y + 0.5f) - it.y0) / dh; float v = it.v0 + (it.v1 - it.v0) * fy;
        int ty = std::min(th - 1, std::max(0, (int)(v * th)));
        for (int x = std::max(x0, p.vx); x < std::min(x1, p.vx + p.vw); x++) {
          if (x < 0 || x >= W) continue;
          float fx = ((x + 0.5f) - it.x0) / dw; float u = it.u0 + (it.u1 - it.u0) * fx;
          int tx = std::min(tw - 1, std::max(0, (int)(u * tw)));
          const uint8_t* s = src + ((size_t)ty * tw + tx) * 4;
          float a = s[3] / 255.f * it.a; if (a <= 0) continue;
          uint8_t* d = &fb[((size_t)y * W + x) * 4];
          d[0] = (uint8_t)(d[0] * (1 - a) + s[0] * it.r * a); d[1] = (uint8_t)(d[1] * (1 - a) + s[1] * it.g * a); d[2] = (uint8_t)(d[2] * (1 - a) + s[2] * it.b * a);
        }
      }
    }
  }
}

static uint32_t crcTable[256];
static uint32_t crc(const uint8_t* p, size_t n, uint32_t c = 0xffffffff) {
  if (!crcTable[1]) for (uint32_t i = 0; i < 256; i++) { uint32_t k = i; for (int j = 0; j < 8; j++) k = k & 1 ? 0xedb88320 ^ (k >> 1) : k >> 1; crcTable[i] = k; }
  for (size_t i = 0; i < n; i++) c = crcTable[(c ^ p[i]) & 255] ^ (c >> 8); return c;
}
static void be32(std::vector<uint8_t>& o, uint32_t v) { o.push_back(v >> 24); o.push_back(v >> 16); o.push_back(v >> 8); o.push_back(v); }
static void chunk(std::vector<uint8_t>& o, const char* type, const std::vector<uint8_t>& d) {
  be32(o, (uint32_t)d.size()); size_t s = o.size(); o.insert(o.end(), type, type + 4); o.insert(o.end(), d.begin(), d.end());
  be32(o, crc(&o[s], d.size() + 4) ^ 0xffffffff);
}
static bool writePng(const char* path, const std::vector<uint8_t>& rgba, int W, int H) {
  std::vector<uint8_t> raw; for (int y = 0; y < H; y++) { raw.push_back(0); raw.insert(raw.end(), &rgba[(size_t)y * W * 4], &rgba[(size_t)y * W * 4] + W * 4); }
  std::vector<uint8_t> z = { 0x78, 0x01 }; uint32_t a = 1, b = 0;
  for (size_t i = 0; i < raw.size(); i += 65535) {
    size_t n = std::min<size_t>(65535, raw.size() - i); z.push_back(i + n == raw.size() ? 1 : 0);
    z.push_back(n & 255); z.push_back(n >> 8); z.push_back(~n & 255); z.push_back((~n >> 8) & 255);
    z.insert(z.end(), raw.begin() + i, raw.begin() + i + n);
  }
  for (uint8_t c : raw) { a = (a + c) % 65521; b = (b + a) % 65521; } be32(z, (b << 16) | a);
  std::vector<uint8_t> o = { 0x89, 'P', 'N', 'G', 13, 10, 26, 10 }, hdr; be32(hdr, W); be32(hdr, H); hdr.push_back(8); hdr.push_back(6); hdr.push_back(0); hdr.push_back(0); hdr.push_back(0);
  chunk(o, "IHDR", hdr); chunk(o, "IDAT", z); chunk(o, "IEND", {});
  FILE* f = fopen(path, "wb"); if (!f) return false; fwrite(o.data(), 1, o.size(), f); fclose(f); return true;
}

void rasterizePasses(const std::vector<engine::CameraPass>& passes, std::vector<uint8_t>& fb, int W, int H, bool clearBlack);
namespace cs { void watchdogStart(); void watchdogBeat(); }
void engineDebugDump();
#ifdef DE_LEAKCHECK
void engineLiveDump(const char* path);
#endif
void engineProfileReport();
struct Click { float x, y; int frame; int button; };
int main(int argc, char** argv) {
  if (argc < 6) { printf("usage: detest data save scene frames out.png [--viewer] [--click x,y@f] [--rclick x,y@f] [--key code@f] [--shot f:path]\n"); return 1; }
  std::string data = argv[1], save = argv[2]; int scene = atoi(argv[3]), frames = atoi(argv[4]); const char* out = argv[5];
  int memEvery = 0; bool viewer = false, dump = false; const char* wavPath = nullptr; std::vector<int> playClips; std::vector<std::pair<int, int>> gotos; std::vector<int16_t> wav; std::vector<Click> clicks; std::vector<std::pair<int, int>> keys; std::vector<std::pair<int, std::string>> shots;
  for (int i = 6; i < argc; i++) {
    if (!strcmp(argv[i], "--viewer")) viewer = true;
    else if (!strcmp(argv[i], "--wav") && i + 1 < argc) wavPath = argv[++i];
    else if (!strcmp(argv[i], "--dump")) dump = true;
    else if (!strcmp(argv[i], "--mem") && i + 1 < argc) memEvery = atoi(argv[++i]);   // print private memory every N frames
    else if (!strcmp(argv[i], "--goto") && i + 1 < argc) { int sc, f; sscanf(argv[i + 1], "%d@%d", &sc, &f); gotos.push_back({ sc, f }); i++; }
    else if (!strcmp(argv[i], "--playclip") && i + 1 < argc) playClips.push_back(atoi(argv[++i]));
    else if ((!strcmp(argv[i], "--click") || !strcmp(argv[i], "--rclick")) && i + 1 < argc) { Click c; sscanf(argv[i + 1], "%f,%f@%d", &c.x, &c.y, &c.frame); c.button = argv[i][2] == 'r' ? 1 : 0; clicks.push_back(c); i++; }
    else if (!strcmp(argv[i], "--key") && i + 1 < argc) { int k, f; sscanf(argv[i + 1], "%d@%d", &k, &f); keys.push_back({ k, f }); i++; }
    else if (!strcmp(argv[i], "--shot") && i + 1 < argc) { int f; char p[512]; sscanf(argv[i + 1], "%d:%511s", &f, p); shots.push_back({ f, p }); i++; }
  }
  _mkdir(save.c_str());
  engine::setViewerMode(viewer);
  if (!engine::init(data, save)) { printf("init failed\n"); return 2; }
  cs::watchdogStart();
  engine::loadSceneNow(scene);
  for (int c : playClips) printf("play clip %d -> voice %d\n", c, audio::play(c, 1, 1, 0, false, 0, false, false));
  engine::InputState in;
  std::vector<uint8_t> fb; std::vector<engine::CameraPass> passes;
  for (int f = 1; f <= frames; f++) {
    in.mouse[0] = in.mouse[1] = false;
    for (auto& c : clicks) { if (f == c.frame || f == c.frame + 1) { in.mouseX = c.x; in.mouseY = engine::SCREEN_H - c.y; } if (f == c.frame + 1) in.mouse[c.button] = true; }
    for (auto& k : keys) in.keys[k.first] = (f == k.second);
    engine::setInput(in);
    cs::watchdogBeat();
    for (auto& gt : gotos) if (gt.second == f) SceneManager::LoadScene(gt.first);
    LARGE_INTEGER t0, t1, fq; QueryPerformanceCounter(&t0);
    engine::frame(1.0f / 60);
    QueryPerformanceCounter(&t1); QueryPerformanceFrequency(&fq);
    { double ms = (t1.QuadPart - t0.QuadPart) * 1000.0 / fq.QuadPart; if (ms > 50) { printf("[slow] frame %d took %.0f ms\n", f, ms); fflush(stdout); } }
    if (wavPath) { size_t at = wav.size(); wav.resize(at + 800 * 2); engine::mixAudio(&wav[at], 800, 48000); }
    for (auto& s : shots) if (s.first == f) { engine::buildFrame(passes); rasterizePasses(passes, fb, engine::SCREEN_W, engine::SCREEN_H, true); writePng(s.second.c_str(), fb, engine::SCREEN_W, engine::SCREEN_H); }
#ifdef DE_LEAKCHECK
    for (auto& s : shots) if (s.first == -f) engineLiveDump(s.second.c_str());
#endif
    if (memEvery && f % memEvery == 0) { PROCESS_MEMORY_COUNTERS_EX pm{}; GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pm, sizeof pm); printf("[mem] frame %d: %.1f MB\n", f, pm.PrivateUsage / 1048576.0); fflush(stdout); }
    if (engine::quitRequested()) break;
  }
  if (dump) engineDebugDump();
  engineProfileReport();
  engine::buildFrame(passes);
  rasterizePasses(passes, fb, engine::SCREEN_W, engine::SCREEN_H, true);
  writePng(out, fb, engine::SCREEN_W, engine::SCREEN_H);
  if (wavPath) {
    FILE* f = fopen(wavPath, "wb");
    if (f) { uint32_t data = (uint32_t)(wav.size() * 2), riff = 36 + data, fmtLen = 16, rate = 48000, bps = 48000 * 4; uint16_t pcm = 1, ch = 2, align = 4, bits = 16;
      fwrite("RIFF", 1, 4, f); fwrite(&riff, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f); fwrite(&fmtLen, 4, 1, f); fwrite(&pcm, 2, 1, f); fwrite(&ch, 2, 1, f);
      fwrite(&rate, 4, 1, f); fwrite(&bps, 4, 1, f); fwrite(&align, 2, 1, f); fwrite(&bits, 2, 1, f); fwrite("data", 1, 4, f); fwrite(&data, 4, 1, f); fwrite(wav.data(), 2, wav.size(), f); fclose(f); }
    int peak = 0; for (int16_t s : wav) peak = std::max(peak, std::abs((int)s)); printf("audio: %.1fs, peak %d\n", wav.size() / 2 / 48000.0, peak);
  }
  int items = 0; for (auto& p : passes) items += (int)p.items.size();
  printf("done: %zu camera passes, %d sprites, %d script errors\n", passes.size(), items, engine::scriptErrors());
  engine::shutdown();
  return 0;
}
