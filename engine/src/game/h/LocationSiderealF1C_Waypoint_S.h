// Generated from LocationSiderealF1C_Waypoint_S.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF1C_Waypoint_S.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF1C_Waypoint_S : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> pipe{};
  P<Sprite> door{};
  P<Sprite> open{};
  P<PolygonCollider2D> pipeobs{};
  P<GameObject> actionMarker1{};
  P<GameObject> actionMarker2{};
  // ---- constructors
  LocationSiderealF1C_Waypoint_S() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void pushLittleCart();
  void positionThem();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
