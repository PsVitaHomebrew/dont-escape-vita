// Generated from OutpostAreaRadar.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostAreaRadar.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class OutpostAreaRadar : public AreaEffect {
public:
  // ---- constructors
  OutpostAreaRadar() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
