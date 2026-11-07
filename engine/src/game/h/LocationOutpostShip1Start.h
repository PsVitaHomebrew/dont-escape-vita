// Generated from LocationOutpostShip1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpostShip1Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpostShip1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> playerShadow{};
  float modX{};
  float modY{};
  bool clambino{};
  // ---- constructors
  LocationOutpostShip1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
