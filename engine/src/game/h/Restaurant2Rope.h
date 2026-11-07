// Generated from Restaurant2Rope.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant2Rope.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant2Rope : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> lever1{};
  P<Sprite> lever2{};
  // ---- constructors
  Restaurant2Rope() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void lowerFlag();
  void drop(String name);
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
