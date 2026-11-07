// Generated from Waypoint_GasstationRoom1_Gasstation1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_GasstationRoom1_Gasstation1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_GasstationRoom1_Gasstation1 : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_GasstationRoom1_Gasstation1() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick() override;
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
