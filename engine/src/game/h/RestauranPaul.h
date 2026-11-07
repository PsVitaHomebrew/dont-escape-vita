// Generated from RestauranPaul.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RestauranPaul.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RestauranPaul : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> sarge{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 color; // = new Vector3(253f / 255f, 106f / 255f, 2f / 255f)  (set in _cctor)
  P<SpriteShadow> shadow{};
  Vector3 position{};
  Vector2 position2{};
  P<Sprite> last{};
  bool enabledd{};
  // ---- constructors
  RestauranPaul() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void initIntroDialogue();
  void takeDoc(int i);
  void gingerTurn(String a = S(""));
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
