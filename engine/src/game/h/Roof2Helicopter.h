// Generated from Roof2Helicopter.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Roof2Helicopter.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Roof2Helicopter : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> tarpaulin{};
  P<Sprite> taped{};
  // ---- constructors
  Roof2Helicopter() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void yesClick();
  void yesClick2();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
