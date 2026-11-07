// Generated from LanguageSelectorButton.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LanguageSelectorButton.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LanguageSelectorButton : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> flag_pl{};
  P<Sprite> flag_en{};
  P<Sprite> flag_de{};
  P<SpriteRenderer> flag{};
  P<LanguageSelectorCaption> languageSelectorCaption{};
  P<DialogueOptionController> doc{};
  // ---- constructors
  LanguageSelectorButton() {}
  // ---- methods
  void Start();
  void takeDoc(int i);
  void clickAction() override;
  void changeLanguage(String lang);
  void endTalk(String val = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
