// Generated from LocationSiderealRoof_Waypoint_F3S.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealRoof_Waypoint_F3S.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealRoof_Waypoint_F3S : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealRoof_Waypoint_F3S() {}
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
