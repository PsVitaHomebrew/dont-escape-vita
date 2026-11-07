// Generated from TextRightScript.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TextRightScript.cpp
#pragma once
#include "../game_types.h"

class TextRightScript : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> tLEFT{};
  P<TextFieldController> tRIGHT{};
  String textToType{}; // C# init: GameStrings.getString(GameStrings.journal, "entry_intro")  (do it in the constructor)
  P<GameObject> nextBtn{};
  P<GameObject> prevBtn{};
  int currentPage{};
  bool rewinded{};
  List<String> pages{};
  // ---- constructors
  TextRightScript();
  // ---- methods
  void Start();
  void gotoNextPage();
  void gotoPrevPage();
  void Update();
  void viewText(P<TextFieldController> tf, String text);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
