// Generated from LocationSiderealF1C_BlockedStairs.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF1C_BlockedStairs.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF1C_BlockedStairs : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealF1C_BlockedStairs() {}
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
