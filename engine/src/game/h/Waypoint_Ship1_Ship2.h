// Generated from Waypoint_Ship1_Ship2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Ship1_Ship2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Ship1_Ship2 : public ObjectActionController {
public:
  // ---- fields
  P<LocationOutpostShip1Start> loss{};
  // ---- constructors
  Waypoint_Ship1_Ship2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void rideDown();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
