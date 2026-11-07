// Generated from LocationSiderealF2CStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF2CStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF2CStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> overLight{};
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> doorlight{};
  P<SpriteRenderer> darkness{};
  P<NPCWalkController> cody{};
  // ---- constructors
  LocationSiderealF2CStart() {}
  // ---- methods
  void Start();
  void codyRun(String s = S(""));
  void Update();
  void turn_south(String var = S(""));
  void turn_south_east(String var = S(""));
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
