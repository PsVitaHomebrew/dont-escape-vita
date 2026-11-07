// Generated from AirplaneGround.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/AirplaneGround.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class AirplaneGround : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> ground{};
  P<SpriteRenderer> plane{};
  // ---- constructors
  AirplaneGround() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void yesDig();
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
