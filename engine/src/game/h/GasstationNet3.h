// Generated from GasstationNet3.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationNet3.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationNet3 : public ObjectActionController {
public:
  // ---- constructors
  GasstationNet3() {}
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
