// Generated from HuntersLodgeScratches.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeScratches.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeScratches : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> gas{};
  P<Sprite> bugs{};
  P<Sprite> spiders{};
  // ---- constructors
  HuntersLodgeScratches() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void standup(String param = S(""));
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
