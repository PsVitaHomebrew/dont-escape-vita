// Generated from HuntersLodgeHatch.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeHatch.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeHatch : public ObjectActionController {
public:
  // ---- constructors
  HuntersLodgeHatch() {}
  // ---- methods
  void Start();
  void yesClearIt();
  void noCliear();
  void doneClearing();
  void standup(String param = S(""));
  void pickItUp(String param);
  void clickAction() override;
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
