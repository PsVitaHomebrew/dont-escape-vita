// Generated from LocationMoonbase3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonbase3Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoonbase3Start : public MonoBehaviour {
public:
  // ---- fields
  float time{};
  P<AudioSource> audioSouruce{};
  P<AudioSource> audioSouruce2{};
  P<AudioSource> rumbler{};
  P<MoonbaseLightFlicker> mlf{};
  bool walkingHere{};
  // ---- constructors
  LocationMoonbase3Start() {}
  // ---- methods
  void Start();
  void walkToMiddle(String s = S(""));
  void close_david_pod();
  void go_to_sleep();
  void updateMLF();
  void startDialogue(String str_ = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
