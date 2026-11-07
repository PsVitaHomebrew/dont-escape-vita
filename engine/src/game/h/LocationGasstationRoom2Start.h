// Generated from LocationGasstationRoom2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationGasstationRoom2Start.cpp
#pragma once
#include "../game_types.h"

class LocationGasstationRoom2Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> thug{};
  P<SpriteRenderer> sargeA{};
  P<SpriteRenderer> sargeB{};
  P<SpriteRenderer> sargeC{};
  // ---- constructors
  LocationGasstationRoom2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
