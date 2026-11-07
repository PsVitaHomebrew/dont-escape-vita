// Generated from LocationSiderealF0C2_Waypoint_Outside.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0C2_Waypoint_Outside.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF0C2_Waypoint_Outside : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> light2{};
  P<SpriteRenderer> overlight{};
  // ---- constructors
  LocationSiderealF0C2_Waypoint_Outside() {}
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
