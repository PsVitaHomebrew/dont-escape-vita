// Generated from JukeboxMusic.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/JukeboxMusic.cpp
#pragma once
#include "../game_types.h"

class JukeboxMusic : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> audioSource{};
  static P<JukeboxMusic> jb;
  P<AudioClip> currentMusic{};
  P<AudioClip> nextMusic{};
  float musicVolume = 0.5f;
  float currentPlaybackVolume{};
  float targetPlaybackVolume{};
  float step = 0.1f;
  bool loop = true;
  float delayMin{};
  float delayMax{};
  float delay{};
  float currentDelay{};
  // ---- constructors
  JukeboxMusic() {}
  // ---- methods
  P<AudioClip> getCurrentMusic();
  void Awake();
  void Start();
  void Update();
  void changeMusic(P<AudioClip> newMusic, bool looping = true, float minTime = 15.0f, float maxTime = 80.0f, float newStep = 0.1f);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
