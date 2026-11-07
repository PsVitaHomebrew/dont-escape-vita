// Generated from Waypoint_Crashsite1_Crossroad.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Crashsite1_Crossroad.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Crashsite1_Crossroad : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Crashsite1_Crossroad() {}
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
