// Generated from LocationSiderealF3CStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF3CStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF3CStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF3CStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
