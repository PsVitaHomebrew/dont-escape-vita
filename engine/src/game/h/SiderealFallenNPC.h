// Generated from SiderealFallenNPC.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealFallenNPC.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealFallenNPC : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> barry{};
  P<Sprite> cody{};
  P<Sprite> grave{};
  // ---- constructors
  SiderealFallenNPC() {}
  // ---- methods
  void Start();
  void bury();
  void cateTalk();
  void clickAction() override;
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
