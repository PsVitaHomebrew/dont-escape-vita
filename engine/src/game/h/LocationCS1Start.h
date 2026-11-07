// Generated from LocationCS1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCS1Start.cpp
#pragma once
#include "../game_types.h"

class LocationCS1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> guards{};
  // ---- constructors
  LocationCS1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
