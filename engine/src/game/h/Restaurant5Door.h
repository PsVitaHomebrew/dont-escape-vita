// Generated from Restaurant5Door.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant5Door.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant5Door : public ObjectActionController {
public:
  // ---- fields
  P<PolygonCollider2D> block{};
  P<PolygonCollider2D> block2{};
  P<SpriteRenderer> shadow{};
  // ---- constructors
  Restaurant5Door() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void shadowpop();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
