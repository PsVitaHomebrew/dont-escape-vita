// Generated from WaypointRestaurant53.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/WaypointRestaurant53.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class WaypointRestaurant53 : public ObjectActionController {
public:
  // ---- constructors
  WaypointRestaurant53() {}
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
