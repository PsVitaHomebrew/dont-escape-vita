// Generated from LocationSiderealF0Ca_Waypoint_Lab.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0Ca_Waypoint_Lab.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF0Ca_Waypoint_Lab : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealF0Ca_Waypoint_Lab() {}
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
