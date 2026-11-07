// Generated from Restaurant4Can.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant4Can.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant4Can : public ObjectActionController {
public:
  // ---- constructors
  Restaurant4Can() {}
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
