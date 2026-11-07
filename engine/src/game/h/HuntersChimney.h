// Generated from HuntersChimney.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersChimney.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersChimney : public ObjectActionController {
public:
  // ---- constructors
  HuntersChimney() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
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
