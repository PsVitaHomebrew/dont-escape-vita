// Generated from LocationRV2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRV2Start.cpp
#pragma once
#include "../game_types.h"

class LocationRV2Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationRV2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
