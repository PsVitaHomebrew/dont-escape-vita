// Generated from CS5_Hook.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS5_Hook.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS5_Hook : public ObjectActionController {
public:
  // ---- constructors
  CS5_Hook() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
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
