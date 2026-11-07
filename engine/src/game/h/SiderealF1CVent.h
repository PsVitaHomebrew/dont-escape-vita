// Generated from SiderealF1CVent.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealF1CVent.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealF1CVent : public ObjectActionController {
public:
  // ---- constructors
  SiderealF1CVent() {}
  // ---- methods
  void Start();
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
