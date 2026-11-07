// Generated from FontSelectorStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/FontSelectorStart.cpp
#pragma once
#include "../game_types.h"

class FontSelectorStart : public MonoBehaviour {
public:
  // ---- fields
  P<DialogueOptionController> doc{};
  P<TextFieldController> caption{};
  P<TextFieldController> caption2{};
  P<TextFieldController> bottom{};
  P<TextFieldController> languageCaption{};
  P<LanguageSelectorCaption> languageIcon{};
  // ---- constructors
  FontSelectorStart() {}
  // ---- methods
  void Start();
  void selectPixel();
  void previewPixel();
  void selectSmooth();
  void previewSmooth();
  void pickFont();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
