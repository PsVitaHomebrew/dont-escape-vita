// Generated from FirstEncounterCrossroad.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/FirstEncounterCrossroad.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class FirstEncounterCrossroad : public ObjectActionController {
public:
  // ---- constructors
  FirstEncounterCrossroad() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
