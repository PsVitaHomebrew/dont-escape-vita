// Generated from HuntersLodgeCable.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeCable.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HuntersLodgeCable : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> cord{};
  P<Sprite> cord2{};
  // ---- constructors
  HuntersLodgeCable() {}
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
