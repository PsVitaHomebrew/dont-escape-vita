// Generated from LanguageSelectorCaption.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LanguageSelectorCaption.cpp
#pragma once
#include "../game_types.h"

class LanguageSelectorCaption : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> t{};
  // ---- constructors
  LanguageSelectorCaption() {}
  // ---- methods
  void Start();
  void updateText();
  void hideText();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
