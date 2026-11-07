// Generated from CS2Maggot.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS2Maggot.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS2Maggot : public ObjectActionController {
public:
  // ---- fields
  P<CursorController> cursorController{};
  // ---- constructors
  CS2Maggot() {}
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
