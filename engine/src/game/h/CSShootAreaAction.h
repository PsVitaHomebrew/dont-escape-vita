// Generated from CSShootAreaAction.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CSShootAreaAction.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class CSShootAreaAction : public AreaEffect {
public:
  // ---- fields
  P<LocationCS2Start> cs2{};
  P<ObjectActionController> exitcs1{};
  P<ObjectActionController> exitcs3{};
  // ---- constructors
  CSShootAreaAction() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
