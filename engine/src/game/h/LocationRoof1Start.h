// Generated from LocationRoof1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRoof1Start.cpp
#pragma once
#include "../game_types.h"

class LocationRoof1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> moon{};
  P<SpriteRenderer> moong{};
  P<Sprite> moon2{};
  P<Sprite> moon3{};
  P<Sprite> moon4{};
  P<Sprite> moon2g{};
  P<Sprite> moon3g{};
  P<Sprite> moon4g{};
  P<SpriteRenderer> destroyedRoof{};
  // ---- constructors
  LocationRoof1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
