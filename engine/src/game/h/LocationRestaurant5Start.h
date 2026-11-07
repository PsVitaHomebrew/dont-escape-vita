// Generated from LocationRestaurant5Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRestaurant5Start.cpp
#pragma once
#include "../game_types.h"

class LocationRestaurant5Start : public MonoBehaviour {
public:
  // ---- fields
  P<PolygonCollider2D> block{};
  P<PolygonCollider2D> block2{};
  bool shadowbegone{};
  P<SpriteRenderer> shadow{};
  float al{};
  // ---- constructors
  LocationRestaurant5Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
