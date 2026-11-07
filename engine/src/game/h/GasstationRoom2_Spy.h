// Generated from GasstationRoom2_Spy.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationRoom2_Spy.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationRoom2_Spy : public ObjectActionController {
public:
  // ---- constructors
  GasstationRoom2_Spy() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void goThere(String s = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
