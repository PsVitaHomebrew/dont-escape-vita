// Engine interface used by the platform layers (PC test runner, Vita main).
#pragma once
#include "unity.h"
#include <string>
#include <vector>

namespace engine {

constexpr int SCREEN_W = 960, SCREEN_H = 540; // what scripts see as Screen.width/height (Vita shows it with 2px bars)

struct InputState {
  float mouseX = 480, mouseY = 270;   // Unity screen coordinates: origin bottom-left, 960x540
  bool mouse[3] = { false, false, false };
  bool keys[512] = {};                // indexed by KeyCode value
};

struct DrawItem {
  int tex = -1;                // textures.json index, or -1 with rtex set
  Texture2D* rtex = nullptr;   // runtime texture
  float x0, y0, x1, y1;        // screen pixels, top-left origin
  float u0, v0, u1, v1;        // texture coordinates (0..1, v down)
  float r, g, b, a;
  bool linear = false;
  uint8_t maskMode = 0;        // 0 none, 1 visible inside sprite masks, 2 visible outside
  int maskGroup = -1;          // -1: masks outside any SortingGroup (CameraPass::masks); else index into groupMasks
  uint8_t blend = 0;           // 0 normal alpha, 1 multiply (MultiplyMaterial), 2 additive light (OverlayMaterial)
};
struct CameraPass {
  bool clear = false; float bg[4] = { 0, 0, 0, 1 };
  int vx = 0, vy = 0, vw = SCREEN_W, vh = SCREEN_H;   // viewport, top-left origin
  std::vector<DrawItem> items;
  std::vector<DrawItem> masks; // sprite mask shapes (alpha above maskCutoff counts as inside)
  float maskCutoff = 0.2f;
  std::vector<std::vector<DrawItem>> groupMasks;   // masks inside each SortingGroup only affect that group
  std::vector<float> groupCutoff;
};

bool init(const std::string& dataDir, const std::string& saveDir);
void setInput(const InputState& in);
void frame(float dt);                      // one game frame
void buildFrame(std::vector<CameraPass>& out);
bool quitRequested();
void shutdown();

// Textures: decompress on demand (renderer uploads and frees)
bool loadTexturePixels(int texIndex, std::vector<uint8_t>& rgba, int& w, int& h, const char** why = nullptr);
const char* textureName(int texIndex);
int sceneLoadCount();                       // bumps on every scene load (renderers free the old scene's art)
int textureFilter(int texIndex);
int textureCount();

// Testing helpers
void loadSceneNow(int index);
int sceneCount();
const char* sceneName(int index);
void setViewerMode(bool on);               // no scripts: show scenes as authored
int scriptErrors();

// Audio mixing (platform pulls PCM)
void mixAudio(int16_t* out, int frames, int rate);

} // namespace engine
