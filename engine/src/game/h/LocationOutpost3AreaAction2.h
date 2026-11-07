// Generated from LocationOutpost3AreaAction2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost3AreaAction2.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class LocationOutpost3AreaAction2 : public AreaEffect {
public:
  // ---- constructors
  LocationOutpost3AreaAction2() {}
  // ---- methods
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
