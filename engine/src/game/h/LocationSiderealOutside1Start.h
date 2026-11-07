// Generated from LocationSiderealOutside1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealOutside1Start.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealOutside1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> plane1{};
  P<SpriteRenderer> plane2{};
  // ---- constructors
  LocationSiderealOutside1Start() {}
  // ---- methods
  void Start();
  void talkafterawhile();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
