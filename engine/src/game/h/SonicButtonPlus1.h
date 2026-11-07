// Generated from SonicButtonPlus1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SonicButtonPlus1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SonicButtonPlus1 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> up{};
  P<Sprite> down{};
  int delta{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  SonicButtonPlus1() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void restore();
  void updateAfterAnimation();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
