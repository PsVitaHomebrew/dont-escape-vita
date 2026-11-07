// Generated from HuntersLodgeCouch.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeCouch.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeCouch : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> gas{};
  P<Sprite> bugs{};
  P<Sprite> spiders{};
  // ---- constructors
  HuntersLodgeCouch() {}
  // ---- methods
  void Start();
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
