// Generated from rv_body2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/rv_body2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class rv_body2 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> gas{};
  P<Sprite> bugs{};
  P<Sprite> ice{};
  P<Sprite> heat{};
  P<Sprite> spiders{};
  P<Sprite> gone{};
  // ---- constructors
  rv_body2() {}
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
