// Generated from JukeboxPlaylist.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/JukeboxPlaylist.cpp
#pragma once
#include "../game_types.h"

class JukeboxPlaylist : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> music{};
  P<JukeboxPlaylist> jB{};
  float currentVolume{};
  float targetVolume{};
  float step = 0.1f;
  List<P<AudioClip>> playList{};
  // ---- constructors
  JukeboxPlaylist() {}
  // ---- methods
  void Awake();
  void Start();
  void Update();
  void playNextClipOnPlayList();
  void changeMusic(P<AudioClip> newMusic, bool looping);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
