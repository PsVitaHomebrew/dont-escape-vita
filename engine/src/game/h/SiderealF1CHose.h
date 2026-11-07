// Generated from SiderealF1CHose.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealF1CHose.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealF1CHose : public ObjectActionController {
public:
  // ---- fields
  P<CursorController> cursorController{};
  P<SpriteRenderer> sr{};
  P<Sprite> glass{};
  P<Sprite> ready{};
  P<Sprite> done{};
  // ---- constructors
  SiderealF1CHose() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
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
