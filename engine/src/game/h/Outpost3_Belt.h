// Generated from Outpost3_Belt.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost3_Belt.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost3_Belt : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> crack{};
  P<Sprite> spaw{};
  // ---- constructors
  Outpost3_Belt() {}
  // ---- methods
  void Start();
  void yesTake();
  void yesGive();
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
