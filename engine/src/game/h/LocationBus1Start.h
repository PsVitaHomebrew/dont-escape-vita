// Generated from LocationBus1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBus1Start.cpp
#pragma once
#include "../game_types.h"

class LocationBus1Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationBus1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
