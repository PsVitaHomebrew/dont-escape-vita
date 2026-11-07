// Generated from HouseBBackGrave.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HouseBBackGrave.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HouseBBackGrave : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  // ---- constructors
  HouseBBackGrave() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void digGrave();
  void digging_end();
  void digGrave2();
  void exitGrave();
  void exitGrave2();
  void exitGrave2a();
  void exitGrave2b();
  void exitGrave2c();
  void exitGrave2d();
  void exitGrave3();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
