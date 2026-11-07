// Generated from CraneLeverController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CraneLeverController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CraneLeverController : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> position1{};
  P<Sprite> position2{};
  int leverNumber{};
  P<CraneThing> craneThing{};
  String varname = String(u"");
  // ---- constructors
  CraneLeverController() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void noFuel();
  void okokok();
  void unlockPlayer2();
  void unlockPlayer();
  void updateState() override;
  void hideLever();
  void showLever();
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
