// Generated from HunterLodgeCable3.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HunterLodgeCable3.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HunterLodgeCable3 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> cord{};
  P<Sprite> stormcatcher_on{};
  P<Sprite> stormcatcher_off{};
  // ---- constructors
  HunterLodgeCable3() {}
  // ---- methods
  void Start();
  void Update();
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
