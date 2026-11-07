// Generated from LocationAirplane3Pilot.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAirplane3Pilot.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationAirplane3Pilot : public ObjectActionController {
public:
  // ---- constructors
  LocationAirplane3Pilot() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void rotate(String a = S(""));
  void pickItUp();
  void pickItUp1();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
