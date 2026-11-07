// Sound playback: decodes OGG (stb_vorbis) and MP3 (dr_mp3) clips and mixes voices to 16-bit stereo.
// The game thread starts/stops voices; the platform's audio thread calls audio::mix().
#include "audio.h"
#include <mutex>
#include <deque>
#include <algorithm>
#include <map>
#include <memory>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstdio>

#define STB_VORBIS_NO_STDIO
#define STB_VORBIS_NO_PUSHDATA_API
#include "third_party/stb_vorbis.c"
#undef L
#undef C
#undef R
#define DR_MP3_IMPLEMENTATION
#define DR_MP3_NO_STDIO
#include "third_party/dr_mp3.h"

namespace audio {

struct ClipData { std::vector<uint8_t> bytes; bool mp3 = false; size_t lastUse = 0; int users = 0; };

struct Decoder {
  std::shared_ptr<ClipData> clip;
  stb_vorbis* vorb = nullptr; drmp3 mp3; bool mp3ok = false;
  int rate = 44100, channels = 2;
  std::vector<int16_t> mono;   // scratch for mono MP3s
  ~Decoder() { if (vorb) stb_vorbis_close(vorb); if (mp3ok) drmp3_uninit(&mp3); }
  // takes the reference without copying it: shared_ptr counts are not atomic on the Vita build, so they only
  // change under the voice lock (see loaderStep)
  bool open(std::shared_ptr<ClipData>&& c) {
    clip = std::move(c);
    if (clip->mp3) {
      if (!drmp3_init_memory(&mp3, clip->bytes.data(), clip->bytes.size(), nullptr)) return false;
      mp3ok = true; rate = (int)mp3.sampleRate; channels = (int)mp3.channels;
    } else {
      int err = 0; vorb = stb_vorbis_open_memory(clip->bytes.data(), (int)clip->bytes.size(), &err, nullptr);
      if (!vorb) return false;
      stb_vorbis_info inf = stb_vorbis_get_info(vorb); rate = (int)inf.sample_rate; channels = inf.channels;
    }
    return true;
  }
  // stereo interleaved frames; returns frames produced (0 at end)
  int read(int16_t* out, int frames) {
    if (vorb) return stb_vorbis_get_samples_short_interleaved(vorb, 2, out, frames * 2);
    if (mp3ok) {
      if (channels == 2) return (int)drmp3_read_pcm_frames_s16(&mp3, (drmp3_uint64)frames, out);
      if (mono.size() < (size_t)(frames * channels)) mono.resize(frames * channels);
      int n = (int)drmp3_read_pcm_frames_s16(&mp3, (drmp3_uint64)frames, mono.data());
      for (int i = 0; i < n; i++) { int16_t s = mono[i * channels]; out[i * 2] = s; out[i * 2 + 1] = s; }
      return n;
    }
    return 0;
  }
  void seekFrame(long long f) {
    if (f < 0) f = 0;
    if (vorb) stb_vorbis_seek(vorb, (unsigned)f);
    else if (mp3ok) drmp3_seek_to_pcm_frame(&mp3, (drmp3_uint64)f);
  }
};

struct Voice {
  int id; int clip; float volume, pitch, pan; bool loop, ignorePause, ignoreVolume; long long delay; // delay in output frames
  std::unique_ptr<Decoder> dec;
  int16_t buf[2048 * 2]; int bufFrames = 0; int bufPos = 0; double frac = 0; bool ended = false;
  int16_t prevL = 0, prevR = 0;
  bool pending = true; float pendingSeek = 0;   // waiting for the loader thread to open its decoder
};

#ifdef VITA
// std::mutex does nothing on the Vita build (pthread is only weakly linked), and the audio thread
// mixes while the game thread starts and stops voices. Use the kernel's lightweight mutex instead.
#include <psp2/kernel/threadmgr.h>
struct VoiceLock {
  SceKernelLwMutexWork work; bool ok = false;
  void create() { if (!ok) ok = sceKernelCreateLwMutex(&work, "audio_voices", 0, 0, nullptr) >= 0; }
  void lock() { if (ok) sceKernelLockLwMutex(&work, 1, nullptr); }
  void unlock() { if (ok) sceKernelUnlockLwMutex(&work, 1); }
};
static VoiceLock mtx;   // created in init(), before the audio thread starts
#else
struct VoiceLock : std::mutex { void create() {} };
static VoiceLock mtx;
#endif
static std::string dataDir;
static std::vector<std::string> fmt;         // "ogg" / "mp3" per clip
static std::map<int, std::shared_ptr<ClipData>> cache;
static size_t cacheBytes = 0, useCounter = 0;
static std::vector<std::unique_ptr<Voice>> voices;
static int nextId = 1;
static float listenerVolume = 1; static bool listenerPause = false;
static const size_t CACHE_LIMIT = 24u * 1024 * 1024;

// Clips load on a background thread (loaderStep): play() only queues the voice, so the game thread never
// waits on the memory card (a music track is several MB) and the mixer is not held up while a file is read.
static std::deque<int> loadQueue;   // voice ids waiting for a decoder
static Voice* find(int id);
static bool loaderStep();
#ifdef VITA
static int loaderThread(SceSize, void*) { for (;;) if (!loaderStep()) sceKernelDelayThread(2000); return 0; }
#endif

void init(const std::string& dir, const std::vector<std::string>& formats) {
  mtx.create();
  { std::lock_guard<VoiceLock> l(mtx); dataDir = dir; fmt = formats; }
#ifdef VITA
  SceUID t = sceKernelCreateThread("audio_loader", loaderThread, 0x10000110, 0x10000, 0, SCE_KERNEL_CPU_MASK_USER_2, NULL);
  if (t >= 0) sceKernelStartThread(t, 0, NULL);
#endif
}

// under the lock
static std::shared_ptr<ClipData> cachedClip(int clip) {
  auto it = cache.find(clip); if (it == cache.end()) return nullptr;
  it->second->lastUse = ++useCounter; return it->second;
}
// no lock needed: dataDir/fmt do not change after init, and the new ClipData is not shared yet
static std::shared_ptr<ClipData> readClip(int clip) {
  if (clip < 0 || clip >= (int)fmt.size()) return nullptr;
  std::string path = dataDir + "/snd/" + std::to_string(clip) + "." + fmt[clip];
  FILE* f = fopen(path.c_str(), "rb"); if (!f) return nullptr;
  auto c = std::make_shared<ClipData>(); c->mp3 = fmt[clip] == "mp3";
  fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
  try { c->bytes.resize(n > 0 ? n : 0); } catch (const std::bad_alloc&) { fclose(f); return nullptr; }   // out of memory: the sound is skipped (an uncaught throw here aborted the game)
  if (n > 0) fread(c->bytes.data(), 1, n, f); fclose(f);
  return c;
}
// under the lock: keep the clip, evicting least recently used clips that nothing is playing
static void cacheInsert(int clip, std::shared_ptr<ClipData>& c) {
  auto it = cache.find(clip); if (it != cache.end()) { c = it->second; return; }
  c->lastUse = ++useCounter; cache[clip] = c; cacheBytes += c->bytes.size();
  while (cacheBytes > CACHE_LIMIT) {
    int victim = -1; size_t oldest = (size_t)-1;
    for (auto& kv : cache) if (kv.second.use_count() == 1 && kv.second->lastUse < oldest && kv.first != clip) { oldest = kv.second->lastUse; victim = kv.first; }
    if (victim < 0) break;
    cacheBytes -= cache[victim]->bytes.size(); cache.erase(victim);
  }
}
// Opens the decoder of the next queued voice. Returns false when the queue is empty.
// Every shared_ptr copy or release happens under the lock (counts are not atomic on the Vita build).
static bool loaderStep() {
  int id, clip; float seekT; std::shared_ptr<ClipData> data;
  {
    std::lock_guard<VoiceLock> l(mtx);
    if (loadQueue.empty()) return false;
    id = loadQueue.front(); loadQueue.pop_front();
    Voice* v = find(id); if (!v || !v->pending) return true;
    clip = v->clip; seekT = v->pendingSeek; data = cachedClip(clip);
  }
  if (!data) {
    std::shared_ptr<ClipData> fresh = readClip(clip);   // the slow part: reading the file
    std::lock_guard<VoiceLock> l(mtx);
    if (fresh) cacheInsert(clip, fresh);
    data = std::move(fresh);
  }
  std::unique_ptr<Decoder> dec;
  bool ok = false;
  if (data) {
    dec = std::make_unique<Decoder>();
    ok = dec->open(std::move(data));
    if (ok && seekT > 0) dec->seekFrame((long long)(seekT * dec->rate));
  }
  std::lock_guard<VoiceLock> l(mtx);
  Voice* v = find(id);
  if (v && v->pending) {
    if (ok) { v->dec = std::move(dec); v->pending = false; }
    else { v->pending = false; v->ended = true; v->loop = false; }   // missing or unreadable file: the voice ends
  }
  dec.reset(); data.reset();   // anything not handed over is released here, under the lock
  return true;
}

int play(int clip, float volume, float pitch, float pan, bool loop, float delaySeconds, bool ignorePause, bool ignoreVolume, float startTime) {
  int id;
  {
    std::lock_guard<VoiceLock> l(mtx);
    if (clip < 0 || clip >= (int)fmt.size()) return -1;
    auto v = std::make_unique<Voice>();
    v->id = nextId++; v->clip = clip; v->volume = volume; v->pitch = pitch; v->pan = pan; v->loop = loop;
    v->ignorePause = ignorePause; v->ignoreVolume = ignoreVolume; v->delay = (long long)(delaySeconds * 48000);
    v->pendingSeek = startTime > 0 ? startTime : 0;
    id = v->id; voices.push_back(std::move(v)); loadQueue.push_back(id);
  }
#ifndef VITA
  while (loaderStep()) {}   // PC test runner: load right away (deterministic, no extra thread)
#endif
  return id;
}
static Voice* find(int id) { for (auto& v : voices) if (v->id == id) return v.get(); return nullptr; }
void stop(int id) { std::lock_guard<VoiceLock> l(mtx); voices.erase(std::remove_if(voices.begin(), voices.end(), [&](const std::unique_ptr<Voice>& v) { return v->id == id; }), voices.end()); }
void stopAll() { std::lock_guard<VoiceLock> l(mtx); voices.clear(); }
void setVolume(int id, float v) { std::lock_guard<VoiceLock> l(mtx); if (Voice* x = find(id)) x->volume = v; }
void setPitch(int id, float p) { std::lock_guard<VoiceLock> l(mtx); if (Voice* x = find(id)) x->pitch = p; }
void setPan(int id, float p) { std::lock_guard<VoiceLock> l(mtx); if (Voice* x = find(id)) x->pan = p; }
void setLoop(int id, bool lp) { std::lock_guard<VoiceLock> l(mtx); if (Voice* x = find(id)) x->loop = lp; }
void seek(int id, float t) { std::lock_guard<VoiceLock> l(mtx); if (Voice* x = find(id)) { if (x->pending || !x->dec) { x->pendingSeek = t; return; } x->dec->seekFrame((long long)(t * x->dec->rate)); x->bufFrames = x->bufPos = 0; x->ended = false; } }
void setListener(float volume, bool pause) { std::lock_guard<VoiceLock> l(mtx); listenerVolume = volume; listenerPause = pause; }
bool active(int id) { std::lock_guard<VoiceLock> l(mtx); Voice* x = find(id); return x && !x->ended; }

static bool nextFrame(Voice* v, int16_t& L, int16_t& R) {
  if (v->bufPos >= v->bufFrames) {
    v->bufFrames = v->dec->read(v->buf, 2048); v->bufPos = 0;
    if (v->bufFrames <= 0) {
      if (!v->loop) { v->ended = true; return false; }
      v->dec->seekFrame(0); v->bufFrames = v->dec->read(v->buf, 2048);
      if (v->bufFrames <= 0) { v->ended = true; return false; }
    }
  }
  L = v->buf[v->bufPos * 2]; R = v->buf[v->bufPos * 2 + 1]; v->bufPos++; return true;
}

void mix(int16_t* out, int frames, int rate) {
  static std::vector<float> acc;   // only the audio thread mixes; reusing it avoids a heap allocation per block
  acc.assign((size_t)frames * 2, 0.f);
  // Each voice is mixed under its own short lock, so the game thread never waits for more than one voice's
  // decoding (holding the lock for all voices made sound calls on the game thread stall for milliseconds).
  for (size_t idx = 0;; idx++) {
    std::lock_guard<VoiceLock> l(mtx);
    if (idx >= voices.size()) break;
    {
      Voice* v = voices[idx].get(); if (v->ended || v->pending || !v->dec) continue;
      if (listenerPause && !v->ignorePause) continue;
      float vol = v->volume * (v->ignoreVolume ? 1.f : listenerVolume);
      float lg = vol * (v->pan > 0 ? 1 - v->pan : 1), rg = vol * (v->pan < 0 ? 1 + v->pan : 1);
      double step = (double)v->dec->rate / rate * std::fabs(v->pitch > 0.01f ? v->pitch : 0.01f);
      for (int i = 0; i < frames; i++) {
        if (v->delay > 0) { v->delay--; continue; }
        v->frac += step;
        while (v->frac >= 1.0) { int16_t a, b; if (!nextFrame(v, a, b)) break; v->prevL = a; v->prevR = b; v->frac -= 1.0; }
        if (v->ended) break;
        acc[i * 2] += v->prevL * lg; acc[i * 2 + 1] += v->prevR * rg;
      }
    }
  }
  {
    std::lock_guard<VoiceLock> l(mtx);
    voices.erase(std::remove_if(voices.begin(), voices.end(), [](const std::unique_ptr<Voice>& v) { return v->ended && !v->loop; }), voices.end());
  }
  for (int i = 0; i < frames * 2; i++) { float s = acc[i]; out[i] = (int16_t)(s > 32767 ? 32767 : s < -32768 ? -32768 : s); }
}
} // namespace audio
