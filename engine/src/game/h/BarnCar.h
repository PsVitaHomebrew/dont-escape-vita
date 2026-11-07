// Generated from BarnCar.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnCar.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnCar : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> wheel_broken{};
  P<Sprite> broken{};
  P<Sprite> fixedC{};
  P<GameObject> action1{};
  P<GameObject> action2{};
  float groundItemsFix_x{};
  float groundItemsFix_y{};
  float groundItemsFixShiftX{};
  float groundItemsFixShiftY{};
  // ---- constructors
  BarnCar() {}
  // ---- methods
  void Start();
  void yesFuel();
  void yesFuel2();
  void yesCoil();
  void yesBattery();
  void yesWheel();
  void yesExamine();
  void sayAboutCarFuel();
  void sayAboutCarPart();
  void sayAboutCarExamine();
  bool sayWhatsWrong();
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
