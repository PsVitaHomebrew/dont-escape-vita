// Generated from OutpostAreaDoormat.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostAreaDoormat.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class OutpostAreaDoormat : public AreaEffect {
public:
  // ---- fields
  P<SpriteRenderer> mataEl{};
  P<LocationOutpostOutside2Start> loc{};
  // ---- constructors
  OutpostAreaDoormat() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
