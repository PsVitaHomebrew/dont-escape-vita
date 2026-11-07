// Generated from Waypoint_Bridge_Ravine.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Bridge_Ravine.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Bridge_Ravine : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Bridge_Ravine() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void yesClicked();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
