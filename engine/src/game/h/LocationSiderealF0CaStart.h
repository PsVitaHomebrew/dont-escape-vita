// Generated from LocationSiderealF0CaStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0CaStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF0CaStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF0CaStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
