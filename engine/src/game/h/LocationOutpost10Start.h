// Generated from LocationOutpost10Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost10Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost10Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationOutpost10Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
