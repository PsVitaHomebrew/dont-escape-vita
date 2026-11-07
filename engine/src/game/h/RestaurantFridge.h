// Generated from RestaurantFridge.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantFridge.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantFridge : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> closed{};
  P<Sprite> open_2{};
  P<Sprite> open_1{};
  P<Sprite> open_0{};
  P<Sprite> open_2b{};
  P<Sprite> open_1b{};
  P<Sprite> open_0b{};
  // ---- constructors
  RestaurantFridge() {}
  // ---- methods
  void Start();
  void opensond();
  void break_glass();
  void otherOpen();
  void crowbarOpen();
  void clickAction() override;
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
