// Generated from GasstationCrowbar.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationCrowbar.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationCrowbar : public ObjectActionController {
public:
  // ---- constructors
  GasstationCrowbar() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void giveCrowbar();
  void drop();
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
