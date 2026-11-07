// Generated from FuelController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/FuelController.cpp
#pragma once
#include "../game_types.h"

class FuelController : public MonoBehaviour {
public:
  // ---- fields
  List<P<Sprite>> fuelSprites{};
  List<P<Sprite>> missingSprites{};
  P<TextFieldController> tfc{};
  P<SpriteRenderer> fuelRenderer{};
  P<SpriteRenderer> missingRenderer{};
  P<SpriteRenderer> reservesRenderer{};
  // ---- constructors
  FuelController() {}
  // ---- methods
  int checkFuel();
  float getPercent(int fuelToUse = 0);
  void updateFuelMeter();
  void updateFuelMissingMeter(int fuelToUse);
  void hideFuelMissingMeter();
  void useFuel(int amount);
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
