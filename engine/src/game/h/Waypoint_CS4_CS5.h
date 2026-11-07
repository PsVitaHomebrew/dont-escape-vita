// Generated from Waypoint_CS4_CS5.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_CS4_CS5.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_CS4_CS5 : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_CS4_CS5() {}
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
