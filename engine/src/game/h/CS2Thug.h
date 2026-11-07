// Generated from CS2Thug.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS2Thug.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS2Thug : public ObjectActionController {
public:
  // ---- fields
  P<CSThugSprite> ts{};
  // ---- constructors
  CS2Thug() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void thud();
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
