// Generated from SiderealElectricPinA.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealElectricPinA.cpp
#pragma once
#include "../game_types.h"

class SiderealElectricPinA : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> t{};
  // ---- constructors
  SiderealElectricPinA() {}
  // ---- methods
  void Start();
  void display(String val);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
