// Generated from GasstationTrinkets.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationTrinkets.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationTrinkets : public ObjectActionController {
public:
  // ---- constructors
  GasstationTrinkets() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick() override;
  void whatOnClick0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
