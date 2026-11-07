// Generated from PersistentData.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/PersistentData.cpp
#pragma once
#include "../game_types.h"

class PersistentData : public Obj {
public:
  // ---- fields
  bool disc_cody{};
  bool disc_barry{};
  bool chapter1_spiders{};
  bool chapter1_gas{};
  bool chapter1_locust{};
  bool chapter2_hot{};
  bool chapter2_cold{};
  bool chapter3_bandits{};
  bool chapter3_thunderstorm{};
  bool chapter4_air{};
  bool chapter4_fuel{};
  bool kong_car{};
  bool kong_disk{};
  bool kong_game{};
  bool custom_unlocked{};
  List<P<Objective>> achievements{};
  // ---- constructors
  PersistentData() {}
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
