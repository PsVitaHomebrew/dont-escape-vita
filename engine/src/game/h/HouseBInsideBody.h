// Generated from HouseBInsideBody.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HouseBInsideBody.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HouseBInsideBody : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  P<Collider2D> pathBlocker{};
  // ---- constructors
  HouseBInsideBody() {}
  // ---- methods
  void Start();
  void pickUpLocket(String val = S(""));
  void clickAction() override;
  void moveBody(String val = S(""));
  void updateState() override;
  void whatOnClick() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
