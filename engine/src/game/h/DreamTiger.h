// Generated from DreamTiger.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DreamTiger.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class DreamTiger : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> tiger{};
  P<GameObject> maggie{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 colorTiger; // = new Vector3(134f / 255f, 121f / 255f, 91f / 255f)  (set in _cctor)
  static Vector3 colorMaggie; // = new Vector3(175f / 255f, 98f / 255f, 124f / 255f)  (set in _cctor)
  Vector3 position{};
  Vector2 position2{};
  Vector3 position_b{};
  Vector2 position2_b{};
  P<DreamWraith> dw{};
  P<SpriteShadow> shadow{};
  P<SpriteShadow> shadow2{};
  // ---- constructors
  DreamTiger() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void initIntroDialogue();
  void takeDoc(int i);
  void dialogues();
  void endTalk(String val = S(""));
  void shadowpep(String val = S(""));
  void shadowpep2(String val = S(""));
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
