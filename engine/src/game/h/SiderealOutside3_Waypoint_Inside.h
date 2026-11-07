// Generated from SiderealOutside3_Waypoint_Inside.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealOutside3_Waypoint_Inside.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealOutside3_Waypoint_Inside : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> closed{};
  P<Sprite> open{};
  // ---- constructors
  SiderealOutside3_Waypoint_Inside() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void whatOnClick0() override;
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
