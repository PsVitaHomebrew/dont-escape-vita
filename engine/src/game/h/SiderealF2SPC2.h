// Generated from SiderealF2SPC2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealF2SPC2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealF2SPC2 : public ObjectActionController {
public:
  // ---- constructors
  SiderealF2SPC2() {}
  // ---- methods
  void Start();
  void takeBack(String a = S(""));
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
