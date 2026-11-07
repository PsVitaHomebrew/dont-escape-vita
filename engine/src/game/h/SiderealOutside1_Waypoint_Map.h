// Generated from SiderealOutside1_Waypoint_Map.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealOutside1_Waypoint_Map.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealOutside1_Waypoint_Map : public ObjectActionController {
public:
  // ---- constructors
  SiderealOutside1_Waypoint_Map() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
