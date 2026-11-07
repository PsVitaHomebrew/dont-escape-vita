// Generated from SiderealOutside1_Waypoint_2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealOutside1_Waypoint_2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealOutside1_Waypoint_2 : public ObjectActionController {
public:
  // ---- constructors
  SiderealOutside1_Waypoint_2() {}
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
