// Generated from HuntersLodgeOutside1_Waypoint_Inside.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeOutside1_Waypoint_Inside.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeOutside1_Waypoint_Inside : public ObjectActionController {
public:
  // ---- constructors
  HuntersLodgeOutside1_Waypoint_Inside() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
