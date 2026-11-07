// Generated from Waypoint_Gasstation1_Map.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Gasstation1_Map.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Gasstation1_Map : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Gasstation1_Map() {}
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
