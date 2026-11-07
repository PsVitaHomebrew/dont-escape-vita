// Generated from LocationCS4Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCS4Start.cpp
#pragma once
#include "../game_types.h"

class LocationCS4Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationCS4Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
