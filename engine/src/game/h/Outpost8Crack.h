// Generated from Outpost8Crack.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost8Crack.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost8Crack : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> crack{};
  P<Sprite> spaw{};
  // ---- constructors
  Outpost8Crack() {}
  // ---- methods
  void Start();
  void yesWeld();
  void clickAction() override;
  void gingerwalk(String var = S(""));
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
