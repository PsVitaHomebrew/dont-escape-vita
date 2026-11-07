// Generated from Waypoint_Outpost3_Fusebox.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Outpost3_Fusebox.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Outpost3_Fusebox : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  // ---- constructors
  Waypoint_Outpost3_Fusebox() {}
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
