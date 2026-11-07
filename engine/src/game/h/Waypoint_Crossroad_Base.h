// Generated from Waypoint_Crossroad_Base.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Crossroad_Base.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Crossroad_Base : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Crossroad_Base() {}
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
