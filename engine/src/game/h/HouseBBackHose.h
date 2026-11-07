// Generated from HouseBBackHose.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HouseBBackHose.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HouseBBackHose : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  // ---- constructors
  HouseBBackHose() {}
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
