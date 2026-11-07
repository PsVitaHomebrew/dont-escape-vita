// Generated from BaseChest.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseChest.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BaseChest : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sign{};
  P<Sprite> chestexamine{};
  // ---- constructors
  BaseChest() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void openTheChest();
  void chestTutorial();
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
