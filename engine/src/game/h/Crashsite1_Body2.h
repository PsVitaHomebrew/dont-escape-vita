// Generated from Crashsite1_Body2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Crashsite1_Body2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Crashsite1_Body2 : public ObjectActionController {
public:
  // ---- constructors
  Crashsite1_Body2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void showIt();
  void hideIt();
  void updateState() override;
  void aaa();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
