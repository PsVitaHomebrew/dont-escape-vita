// Generated from CreditsStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CreditsStart.cpp
#pragma once
#include "../game_types.h"

class CreditsStart : public MonoBehaviour {
public:
  // ---- fields
  int skipit = 1;
  float timer{};
  // ---- constructors
  CreditsStart() {}
  // ---- methods
  void Start();
  void mainMenu();
  void showButton();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
