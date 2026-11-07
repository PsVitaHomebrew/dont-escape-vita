// Generated from LocationMoonShipDeadCate.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonShipDeadCate.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationMoonShipDeadCate : public ObjectActionController {
public:
  // ---- fields
  P<TextFieldController> tf{};
  P<Sprite> ded{};
  P<Sprite> ded2{};
  P<Sprite> alive_{};
  // ---- constructors
  LocationMoonShipDeadCate() {}
  // ---- methods
  void Start();
  void playerStandUp(String v = S(""));
  void lookAtMe(String s = S(""));
  void stopLooking(String s = S(""));
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
