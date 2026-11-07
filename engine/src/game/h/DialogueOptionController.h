// Generated from DialogueOptionController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DialogueOptionController.cpp
#pragma once
#include "../game_types.h"

class DialogueOptionController : public MonoBehaviour {
public:
  // ---- fields
  String caption{};
  bool active{};
  bool alphaSet{};
  String objective{};
  P<GameObject> background{};
  List<P<DialogueLine>> lines{};
  P<SpriteRenderer> rend{};
  P<SpriteRenderer> backgroundRend{};
  P<CursorController> cc{};
  int number{};
  float localCooldown{};
  int maxCooldown = 30;
  P<AudioSource> audioSource{};
  // ---- constructors
  DialogueOptionController() {}
  // ---- methods
  void Start();
  void Update();
  void OnMouseEnter();
  void OnMouseDown();
  void OnMouseOver();
  void OnMouseExit();
  void setObjective(String ob);
  void show();
  void hide();
  void initDialogue(List<P<DialogueLine>> dialogueLines, String prefix, P<TextFieldController> tf_a, Vector3 color_a, P<TextFieldController> tf_b, Vector3 color_b, P<TextFieldController> tf_c = nullptr, Vector3 color_c = /*default: default(Vector3)*/{});
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
