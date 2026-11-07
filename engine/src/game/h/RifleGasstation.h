// Generated from RifleGasstation.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RifleGasstation.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RifleGasstation : public ObjectActionController {
public:
  // ---- constructors
  RifleGasstation() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
