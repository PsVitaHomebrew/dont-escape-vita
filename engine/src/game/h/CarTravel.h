// Generated from CarTravel.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CarTravel.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CarTravel : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sign{};
  P<GameObject> trunk{};
  float groundItemsFix_x{};
  float groundItemsFix_y{};
  float groundItemsFixShiftX{};
  float groundItemsFixShiftY{};
  // ---- constructors
  CarTravel() {}
  // ---- methods
  void Start();
  void yesFuel();
  void yesFuel2();
  void sayAboutCarFuel();
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
