// Generated from LocationDay3CutsceneStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay3CutsceneStart.cpp
#pragma once
#include "../game_types.h"

class LocationDay3CutsceneStart : public MonoBehaviour {
public:
  // ---- fields
  float aalfa = -1.0f;
  P<SpriteRenderer> hazy{};
  P<SpriteRenderer> clear{};
  // ---- constructors
  LocationDay3CutsceneStart() {}
  // ---- methods
  void Start();
  void fadeOut(String s = S(""));
  void transportToSidereal(String s = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
