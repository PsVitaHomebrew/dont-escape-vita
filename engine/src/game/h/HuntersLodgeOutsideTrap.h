// Generated from HuntersLodgeOutsideTrap.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeOutsideTrap.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeOutsideTrap : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> corpse{};
  P<ParticleGenerator> pg{};
  // ---- constructors
  HuntersLodgeOutsideTrap() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void clearIt(String param);
  void yesClearIt();
  void noCliear();
  void doneClearing();
  void standup(String param = S(""));
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
