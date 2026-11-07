// Generated from CrashsiteCarClicker.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CrashsiteCarClicker.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CrashsiteCarClicker : public ObjectActionController {
public:
  // ---- constructors
  CrashsiteCarClicker() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void examineCar(String str_);
  void harvestCar(String str_);
  void doHarvestCar();
  void doExamineCar();
  void sayAboutCarHarvest();
  void sayAboutCarExplore();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
