// Generated from HunterLodgeCable2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HunterLodgeCable2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HunterLodgeCable2 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> cord{};
  P<Sprite> cord2{};
  // ---- constructors
  HunterLodgeCable2() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void takeCord(String param = S(""));
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
