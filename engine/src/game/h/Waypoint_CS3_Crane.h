// Generated from Waypoint_CS3_Crane.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_CS3_Crane.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_CS3_Crane : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_CS3_Crane() {}
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
