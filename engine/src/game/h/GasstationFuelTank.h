// Generated from GasstationFuelTank.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationFuelTank.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationFuelTank : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> s1{};
  P<Sprite> s2{};
  // ---- constructors
  GasstationFuelTank() {}
  // ---- methods
  void Start();
  void whatOnClick() override;
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void openTap();
  void valvePlay();
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
