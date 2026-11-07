// Generated from LocationOutpost1_Silo1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost1_Silo1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationOutpost1_Silo1 : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> ground{};
  P<SpriteRenderer> plane{};
  // ---- constructors
  LocationOutpost1_Silo1() {}
  // ---- methods
  void Start();
  void clickAction() override;
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
