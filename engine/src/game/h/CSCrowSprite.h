// Generated from CSCrowSprite.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CSCrowSprite.cpp
#pragma once
#include "../game_types.h"

class CSCrowSprite : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  P<Animator> thug{};
  P<LocationCS2Start> cs2{};
  bool free = true;
  // ---- constructors
  CSCrowSprite() {}
  // ---- methods
  void Start();
  void Update();
  void crowAttack();
  void makeCrowSound();
  void plask();
  void makeFlappingSound();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
