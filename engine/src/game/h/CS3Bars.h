// Generated from CS3Bars.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS3Bars.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS3Bars : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> ammobox1{};
  P<Sprite> ammobox2{};
  P<CursorController> cursorController{};
  // ---- constructors
  CS3Bars() {}
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
