// Generated from HouseBBackBody.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HouseBBackBody.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HouseBBackBody : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  // ---- constructors
  HouseBBackBody() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void whatOnClick() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
