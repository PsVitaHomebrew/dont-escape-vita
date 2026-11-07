// Generated from JukeboxAmbient.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/JukeboxAmbient.cpp
#pragma once
#include "../game_types.h"

class JukeboxAmbient : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> audioSource{};
  static P<JukeboxAmbient> jb;
  P<AudioClip> current{};
  P<AudioClip> next{};
  float ambientVolume = 0.5f;
  float currentPlaybackVolume{};
  float targetPlaybackVolume{};
  float nextTargetVolume{};
  float step = 0.1f;
  // ---- constructors
  JukeboxAmbient() {}
  // ---- methods
  void Awake();
  void Start();
  void Update();
  void changeAmbient(P<AudioClip> newAmb, float newVolume, AudioReverbPreset arp = /*default: AudioReverbPreset.Off*/{});
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
