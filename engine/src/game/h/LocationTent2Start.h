// Generated from LocationTent2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationTent2Start.cpp
#pragma once
#include "../game_types.h"

class LocationTent2Start : public MonoBehaviour {
public:
  // ---- fields
  int skipit{};
  float timer{};
  // ---- constructors
  LocationTent2Start() {}
  // ---- methods
  void music1();
  void music2();
  void music3();
  void Start();
  void mainMenu();
  void showButton();
  void exitTent();
  void exitTent3(String v = S(""));
  void exitTent4();
  void exitTent2();
  void showNapisy(String s = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
