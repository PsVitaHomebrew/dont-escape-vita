// Generated from LocationCS5Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCS5Start.cpp
#pragma once
#include "../game_types.h"

class LocationCS5Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationCS5Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
