// Generated from SiderealAreaAction1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealAreaAction1.cpp
#pragma once
#include "../game_types.h"
#include "AreaEffect.h"

class SiderealAreaAction1 : public AreaEffect {
public:
  // ---- fields
  int mode{};
  // ---- constructors
  SiderealAreaAction1() {}
  // ---- methods
  void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
