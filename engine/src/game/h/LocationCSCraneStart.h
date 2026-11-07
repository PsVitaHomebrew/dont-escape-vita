// Generated from LocationCSCraneStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCSCraneStart.cpp
#pragma once
#include "../game_types.h"

class LocationCSCraneStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> craneContrBack{};
  P<CraneLeverController> l1{};
  P<CraneLeverController> l2{};
  P<CraneLeverController> l3{};
  P<CraneThing> craneThing{};
  bool firstTime{};
  // ---- constructors
  LocationCSCraneStart() {}
  // ---- methods
  void Start();
  void zzz();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
