// Generated from Attic2Screwdriver.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Attic2Screwdriver.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Attic2Screwdriver : public ObjectActionController {
public:
  // ---- constructors
  Attic2Screwdriver() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void pickItUp(String param);
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
