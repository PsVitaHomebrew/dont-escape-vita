// Generated from LocationOutpost7Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost7Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost7Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationOutpost7Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
