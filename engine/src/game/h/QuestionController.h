// Generated from QuestionController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/QuestionController.cpp
#pragma once
#include "../game_types.h"

class QuestionController : public MonoBehaviour {
public:
  using PopupType = QuestionController_PopupType;
  // ---- fields
  P<TextFieldController> questionText{};
  P<Button> yes{};
  P<Button> no{};
  float antiDoubleClick{};
  int timeAdded{};
  Button_Delegate onYesClick{};
  Button_Delegate onNoClick{};
  P<SpriteRenderer> darkness{};
  static P<QuestionController> qc;
  P<CursorController> cursorCont{};
  static bool questionAsked;
  // ---- constructors
  QuestionController() {}
  // ---- methods
  void Awake();
  void Start();
  void showQuestion(String label, QuestionController_PopupType type = QuestionController_PopupType::QUESTION, Button_Delegate yesClick = nullptr, int time = 0, int timeSaver = 0, Button_Delegate noClick = nullptr, String customYesLabel = nullptr, String customNoLabel = nullptr, P<Sprite> image = nullptr);
  void timeAndHide();
  void customNo();
  void initCursor();
  void hideQuestion();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
