// Generated from LocationSiderealShadowWall.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealShadowWall.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealShadowWall : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spriteRenderer{};
  P<SpriteRenderer> playerSprite{};
  // ---- constructors
  LocationSiderealShadowWall() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
