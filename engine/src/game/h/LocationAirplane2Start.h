// Generated from LocationAirplane2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAirplane2Start.cpp
#pragma once
#include "../game_types.h"

class LocationAirplane2Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationAirplane2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
