// Generated from MoonShipCloset.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MoonShipCloset.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class MoonShipCloset : public ObjectActionController {
public:
  // ---- constructors
  MoonShipCloset() {}
  // ---- methods
  void Start();
  void wearit(String s = S(""));
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
