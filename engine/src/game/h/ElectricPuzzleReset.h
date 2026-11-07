// Generated from ElectricPuzzleReset.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ElectricPuzzleReset.cpp
#pragma once
#include "../game_types.h"

class ElectricPuzzleReset : public MonoBehaviour {
public:
  // ---- fields
  P<Button> butbut{};
  // ---- constructors
  ElectricPuzzleReset() {}
  // ---- methods
  void Start();
  void Update();
  void showOrNot();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
