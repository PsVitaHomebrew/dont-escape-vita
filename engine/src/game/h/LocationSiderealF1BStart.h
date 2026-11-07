// Generated from LocationSiderealF1BStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF1BStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF1BStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealF1BStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
