// Generated from LocationOutpostOutside1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpostOutside1Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpostOutside1Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationOutpostOutside1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
