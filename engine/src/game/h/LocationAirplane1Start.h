// Generated from LocationAirplane1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAirplane1Start.cpp
#pragma once
#include "../game_types.h"

class LocationAirplane1Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationAirplane1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
