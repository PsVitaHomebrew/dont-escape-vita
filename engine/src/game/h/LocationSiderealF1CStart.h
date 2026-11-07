// Generated from LocationSiderealF1CStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF1CStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF1CStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> red{};
  P<SpriteRenderer> red2{};
  P<SpriteRenderer> black{};
  P<PolygonCollider2D> darkness{};
  P<PolygonCollider2D> pipeobs{};
  // ---- constructors
  LocationSiderealF1CStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
