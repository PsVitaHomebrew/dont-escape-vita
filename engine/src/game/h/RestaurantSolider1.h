// Generated from RestaurantSolider1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestaurantSolider1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestaurantSolider1 : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> sarge{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 color; // = new Vector3(178f / 255f, 1f, 201f / 255f)  (set in _cctor)
  P<SpriteShadow> shadow{};
  int joshOffset = 20;
  Vector3 position{};
  Vector2 position2{};
  bool enabledd{};
  // ---- constructors
  RestaurantSolider1() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void initIntroDialogue();
  void takeDoc(int i);
  void dialogues();
  void giveCatchers(String val = S(""));
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
