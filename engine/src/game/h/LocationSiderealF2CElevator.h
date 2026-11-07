// Generated from LocationSiderealF2CElevator.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF2CElevator.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF2CElevator : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealF2CElevator() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick0() override;
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
