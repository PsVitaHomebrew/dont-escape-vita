// Generated from LocationOutpost11Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost11Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost11Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteMask> playerMask{};
  P<SpriteRenderer> playerShadow{};
  P<SpriteRenderer> playerShadow2{};
  // ---- constructors
  LocationOutpost11Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
