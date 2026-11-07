// Generated from Waypoint_Crane_CS3.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Crane_CS3.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Crane_CS3 : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Crane_CS3() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void climbCrane();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
