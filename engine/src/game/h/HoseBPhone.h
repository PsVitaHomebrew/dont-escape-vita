// Generated from HoseBPhone.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HoseBPhone.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HoseBPhone : public ObjectActionController {
public:
  // ---- constructors
  HoseBPhone() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void gateIsOpen();
  void gateIsOpening();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
