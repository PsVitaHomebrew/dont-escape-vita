// Generated from Restaurant2Trash2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant2Trash2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant2Trash2 : public ObjectActionController {
public:
  // ---- constructors
  Restaurant2Trash2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
