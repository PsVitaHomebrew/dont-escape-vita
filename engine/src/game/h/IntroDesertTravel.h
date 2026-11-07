// Generated from IntroDesertTravel.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/IntroDesertTravel.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class IntroDesertTravel : public ObjectActionController {
public:
  // ---- fields
  Vector2 realPosition{};
  P<Sprite> standSprite{};
  int skipit{};
  float timer{};
  // ---- constructors
  IntroDesertTravel() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void gogo();
  void updateState() override;
  void allowSkip();
  void whatOnClick() override;
  void showSkip();
  void skipIt();
  void showButton();
  void showIntro1();
  void showIntro1b();
  void showIntro2();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
