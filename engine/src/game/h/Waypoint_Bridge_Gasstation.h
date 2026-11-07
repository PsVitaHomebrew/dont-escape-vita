// Generated from Waypoint_Bridge_Gasstation.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Bridge_Gasstation.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Bridge_Gasstation : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Bridge_Gasstation() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
