// Generated from RestaurantSteve.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantSteve.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantSteve : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> sarge{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 color; // = new Vector3(0.6f, 106f / 255f, 0.4f)  (set in _cctor)
  Vector3 position{};
  Vector2 position2{};
  P<GameObject> actionmarker1{};
  P<GameObject> actionmarker2{};
  // ---- constructors
  RestaurantSteve() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void heal(String s = S(""));
  void standup2();
  void standup(String s = S(""));
  void initIntroDialogue();
  void takeDoc(int i);
  void dialogues();
  void endTalk(String val = S(""));
  void Update();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  static void _cctor(); // translator: set the static fields marked (set in _cctor)
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
