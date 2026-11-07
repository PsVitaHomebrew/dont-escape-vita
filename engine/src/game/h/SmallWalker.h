// Generated from SmallWalker.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SmallWalker.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SmallWalker : public ObjectActionController {
public:
  // ---- fields
  Vector2 realPosition{};
  P<Sprite> standSprite{};
  P<SpriteRenderer> title{};
  P<SpriteRenderer> title2{};
  float titleAlpha{};
  float titleAlpha2{};
  int skipit = 1;
  float timer{};
  // ---- constructors
  SmallWalker() {}
  // ---- methods
  void Start();
  void skipIt();
  void Update();
  void showButton();
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
