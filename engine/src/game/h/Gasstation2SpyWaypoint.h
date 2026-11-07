// Generated from Gasstation2SpyWaypoint.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Gasstation2SpyWaypoint.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Gasstation2SpyWaypoint : public ObjectActionController {
public:
  // ---- constructors
  Gasstation2SpyWaypoint() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void goThere(String s = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
