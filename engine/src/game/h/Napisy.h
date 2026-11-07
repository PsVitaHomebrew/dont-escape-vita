// Generated from Napisy.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Napisy.cpp
#pragma once
#include "../game_types.h"

class Napisy : public MonoBehaviour {
public:
  // ---- constructors
  Napisy() {}
  // ---- methods
  void Start();
  void Update();
  void showNapisyS(String s = S(""));
  void showNapisy1();
  void showNapisy2();
  void showNapisy3();
  void showNapisy4();
  void showNapisy5();
  void showNapisy6();
  void showNapisy7();
  void showNapisy8();
  void showNapisy9();
  void showNapisy10();
  void showNapisy11();
  void showNapisy12();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
