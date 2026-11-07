// Generated from LocationSiderealF3SStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF3SStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF3SStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF3SStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
