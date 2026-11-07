// Generated from LocationAirplane3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAirplane3Start.cpp
#pragma once
#include "../game_types.h"

class LocationAirplane3Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationAirplane3Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
