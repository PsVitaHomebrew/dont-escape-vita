// Generated from LocationSiderealClimb_Waypoint_Roof.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealClimb_Waypoint_Roof.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealClimb_Waypoint_Roof : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealClimb_Waypoint_Roof() {}
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
