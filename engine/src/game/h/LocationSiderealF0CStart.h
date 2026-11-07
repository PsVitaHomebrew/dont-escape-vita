// Generated from LocationSiderealF0CStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0CStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF0CStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF0CStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
