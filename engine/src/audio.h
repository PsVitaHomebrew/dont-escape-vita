// Sound mixer interface (see audio.cpp).
#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace audio {
void init(const std::string& dataDir, const std::vector<std::string>& formats); // formats[i] = "ogg"/"mp3" for clip i
int play(int clip, float volume, float pitch, float pan, bool loop, float delaySeconds, bool ignorePause, bool ignoreVolume, float startTime = 0);
void stop(int voice);
void stopAll();
void setVolume(int voice, float v);
void setPitch(int voice, float p);
void setPan(int voice, float p);
void setLoop(int voice, bool loop);
void seek(int voice, float seconds);
bool active(int voice);
void setListener(float volume, bool pause);
void mix(int16_t* out, int frames, int rate);   // called from the audio thread
}
