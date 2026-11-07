// Generated from HouseBArea2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HouseBArea2.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class HouseBArea2 : public AreaEffect {
public:
  // ---- constructors
  HouseBArea2() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
