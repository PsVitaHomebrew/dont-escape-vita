// Generated from HunterLodgeTrap4.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HunterLodgeTrap4.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HunterLodgeTrap4 : public ObjectActionController {
public:
  // ---- constructors
  HunterLodgeTrap4() {}
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
