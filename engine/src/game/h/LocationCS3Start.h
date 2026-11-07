// Generated from LocationCS3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCS3Start.cpp
#pragma once
#include "../game_types.h"

class LocationCS3Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> tlo1{};
  P<SpriteRenderer> tlo2{};
  P<SpriteRenderer> sciana1{};
  P<SpriteRenderer> sciana2{};
  P<SpriteRenderer> dzwig{};
  P<PolygonCollider2D> areaThugs{};
  P<PolygonCollider2D> areaRain1{};
  P<PolygonCollider2D> areaRain2{};
  P<PolygonCollider2D> areaRainFull{};
  // ---- constructors
  LocationCS3Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
