// Generated from LocationOutpost9Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost9Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost9Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationOutpost9Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
