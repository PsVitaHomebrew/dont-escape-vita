// Generated from Restaurant2Window.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant2Window.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant2Window : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> open{};
  P<Sprite> closed{};
  P<GameObject> trashCollider{};
  // ---- constructors
  Restaurant2Window() {}
  // ---- methods
  void Start();
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
