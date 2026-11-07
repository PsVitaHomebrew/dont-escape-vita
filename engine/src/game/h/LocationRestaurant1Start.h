// Generated from LocationRestaurant1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRestaurant1Start.cpp
#pragma once
#include "../game_types.h"

class LocationRestaurant1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> solider1{};
  P<SpriteRenderer> solider2{};
  P<RestaurantSolider1> s1{};
  P<RestaurantSolider2> s2{};
  P<SpriteRenderer> pylon{};
  // ---- constructors
  LocationRestaurant1Start() {}
  // ---- methods
  void Start();
  void playerRotate(String s = S(""));
  void playerSurr(String s = S(""));
  void npcSurr(String s = S(""));
  void cateSurr(String s = S(""));
  void gotoRestaurant(String s = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
