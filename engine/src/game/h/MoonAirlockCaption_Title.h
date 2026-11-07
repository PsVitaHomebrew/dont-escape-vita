// Generated from MoonAirlockCaption_Title.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MoonAirlockCaption_Title.cpp
#pragma once
#include "../game_types.h"

class MoonAirlockCaption_Title : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  P<TextFieldController> t{};
  // ---- constructors
  MoonAirlockCaption_Title() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
