// Generated from LocationSiderealElectricPuzzleStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealElectricPuzzleStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealElectricPuzzleStart : public MonoBehaviour {
public:
  // ---- fields
  bool failsafe{};
  P<SpriteRenderer> s1{};
  P<SpriteRenderer> s2{};
  bool easycome = true;
  P<ElectricPuzzleReset> butbut{};
  // ---- constructors
  LocationSiderealElectricPuzzleStart() {}
  // ---- methods
  void Start();
  void onclick();
  void updateManual();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
