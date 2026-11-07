// Generated from LocationRoof2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRoof2Start.cpp
#pragma once
#include "../game_types.h"

class LocationRoof2Start : public MonoBehaviour {
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
  LocationRoof2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
