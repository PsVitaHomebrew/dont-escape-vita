// Generated from HuntersLodgeInsideOutlet.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeInsideOutlet.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeInsideOutlet : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> cord{};
  P<Sprite> cord2{};
  P<Sprite> heater{};
  P<SpriteRenderer> heaterLight{};
  float lightAlfa{};
  float lightAlfa2{};
  // ---- constructors
  HuntersLodgeInsideOutlet() {}
  // ---- methods
  void Start();
  void Update();
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
