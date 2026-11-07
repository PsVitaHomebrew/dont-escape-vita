// Generated from RestaurantCupboard3.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantCupboard3.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantCupboard3 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> s1{};
  P<Sprite> s2{};
  // ---- constructors
  RestaurantCupboard3() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
