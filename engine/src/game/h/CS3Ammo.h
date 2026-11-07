// Generated from CS3Ammo.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS3Ammo.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS3Ammo : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> ammobox1{};
  P<Sprite> ammobox2{};
  P<CursorController> cursorController{};
  P<SpriteRenderer> box1{};
  P<SpriteRenderer> box2{};
  // ---- constructors
  CS3Ammo() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void aaa();
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
