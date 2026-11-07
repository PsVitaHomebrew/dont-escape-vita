// Generated from LocationDesertFence3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDesertFence3Start.cpp
#pragma once
#include "../game_types.h"

class LocationDesertFence3Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> thePiasek{};
  P<SpriteRenderer> thePiasekB{};
  P<Sprite> sand1{};
  P<Sprite> sand2{};
  P<Sprite> sand3{};
  P<Sprite> sand4{};
  P<Sprite> sand1B{};
  P<Sprite> sand2B{};
  P<Sprite> sand3B{};
  P<Sprite> sand4B{};
  float alpha{};
  float playerMove{};
  float previous{};
  P<Sprite> dropHint{};
  float proc{};
  P<Sprite> hammerDown{};
  P<Sprite> hammerDown2{};
  P<Item> hammer{};
  // ---- constructors
  LocationDesertFence3Start() {}
  // ---- methods
  void Start();
  void showDropHint(String param);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
