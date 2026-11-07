// Generated from BarnConsoleCaption_Off.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnConsoleCaption_Off.cpp
#pragma once
#include "../game_types.h"

class BarnConsoleCaption_Off : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  float colormod = 1.0f;
  P<TextFieldController> t{};
  // ---- constructors
  BarnConsoleCaption_Off() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
