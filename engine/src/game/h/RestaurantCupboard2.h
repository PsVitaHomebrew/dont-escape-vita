// Generated from RestaurantCupboard2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantCupboard2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantCupboard2 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> s1{};
  P<Sprite> s2{};
  // ---- constructors
  RestaurantCupboard2() {}
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
