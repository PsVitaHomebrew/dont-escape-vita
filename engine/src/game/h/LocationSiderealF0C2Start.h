// Generated from LocationSiderealF0C2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0C2Start.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF0C2Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF0C2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
