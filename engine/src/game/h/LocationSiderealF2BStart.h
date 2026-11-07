// Generated from LocationSiderealF2BStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF2BStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF2BStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> p1a{};
  P<SpriteRenderer> p2a{};
  P<SpriteRenderer> p3a{};
  P<SpriteRenderer> p4a{};
  P<SpriteRenderer> p1b{};
  P<SpriteRenderer> p2b{};
  P<SpriteRenderer> p3b{};
  P<SpriteRenderer> p4b{};
  // ---- constructors
  LocationSiderealF2BStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
