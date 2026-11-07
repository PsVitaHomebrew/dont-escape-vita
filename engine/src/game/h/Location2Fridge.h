// Generated from Location2Fridge.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Location2Fridge.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Location2Fridge : public ObjectActionController {
public:
  // ---- constructors
  Location2Fridge() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void closeSound();
  void closeFridge(String param = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
