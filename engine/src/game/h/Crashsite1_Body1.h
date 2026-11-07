// Generated from Crashsite1_Body1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Crashsite1_Body1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Crashsite1_Body1 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> biteBackground{};
  P<Sprite> bite1{};
  P<Sprite> bite2{};
  P<Sprite> bite3{};
  P<Sprite> bite4{};
  // ---- constructors
  Crashsite1_Body1() {}
  // ---- methods
  void Start();
  void showIt();
  void hideIt();
  void clickAction2() override;
  void updateState() override;
  void clickAction() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
