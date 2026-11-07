// Generated from RestaurantSarge.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantSarge.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantSarge : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> sarge{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 color;
  Vector3 position{};
  Vector2 position2{};
  // ---- constructors
  RestaurantSarge() {}
  // ---- methods
  void Start();
  void takeCatcher(String item);
  void clickAction() override;
  void initIntroDialogue();
  void takeDoc(int i);
  void blockanim(String a = S(""));
  void dialogueintro2(String s = S(""));
  void dialogueintro3();
  void atEase(String s = S(""));
  void playerStandUp(String v = S(""));
  void dialogues();
  void endTalk(String val = S(""));
  void addConstruction(String val = S(""));
  void Update();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
