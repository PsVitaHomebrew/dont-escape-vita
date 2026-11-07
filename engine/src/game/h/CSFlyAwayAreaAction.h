// Generated from CSFlyAwayAreaAction.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CSFlyAwayAreaAction.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class CSFlyAwayAreaAction : public AreaEffect {
public:
  // ---- fields
  P<Animator> crow{};
  P<ObjectActionController> exitcs1{};
  P<ObjectActionController> exitcs3{};
  // ---- constructors
  CSFlyAwayAreaAction() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
