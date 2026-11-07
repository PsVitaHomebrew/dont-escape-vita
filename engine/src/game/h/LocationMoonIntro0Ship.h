// Generated from LocationMoonIntro0Ship.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonIntro0Ship.cpp
#pragma once
#include "../game_types.h"

class LocationMoonIntro0Ship : public MonoBehaviour {
public:
  // ---- constructors
  LocationMoonIntro0Ship() {}
  // ---- methods
  void Start();
  void Update();
  void goToNextScene();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
