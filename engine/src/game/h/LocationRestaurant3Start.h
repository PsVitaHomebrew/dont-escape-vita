// Generated from LocationRestaurant3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRestaurant3Start.cpp
#pragma once
#include "../game_types.h"

class LocationRestaurant3Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> solider1{};
  P<SpriteRenderer> solider2{};
  P<SpriteRenderer> solider4{};
  P<SpriteRenderer> soliderStuff1{};
  P<SpriteRenderer> soliderStuff2{};
  P<SpriteRenderer> soliderStuff3{};
  P<SpriteRenderer> soliderStuff4{};
  bool codySurprised{};
  // ---- constructors
  LocationRestaurant3Start() {}
  // ---- methods
  void Start();
  void surr_npc();
  void antisurr_npc();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
