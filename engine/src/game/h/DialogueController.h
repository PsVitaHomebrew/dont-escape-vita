// Generated from DialogueController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DialogueController.cpp
#pragma once
#include "../game_types.h"

class DialogueController : public MonoBehaviour {
public:
  using Callback = DialogueController_Callback;
  // ---- fields
  static P<DialogueController> dc;
  DialogueController_Callback callback{};
  bool talking{};
  bool hidden = true;
  Array<P<GameObject>> dialogueOptions{};
  P<GameObject> frame{};
  P<Sprite> frameNew{};
  P<Sprite> frameOld{};
  P<TextFieldController> bottomTextfield{};
  P<GameObject> upperTextGameObject{};
  P<TextFieldController> upperTextfield{};
  float cooldown{};
  float maxCooldown = 30.0f;
  P<SpriteRenderer> darkness{};
  float darknessAlpha{};
  float lastDarknessAlpha{};
  float targetAlpha = 0.5f;
  float targetColor = 1.0f;
  // ---- constructors
  DialogueController() {}
  // ---- methods
  void Awake();
  void ShowText(String text);
  void HideText();
  void Start();
  void quickDialogue(Vector3 color, P<NPCActionController> who, String what);
  void Update();
  void show();
  void hide();
  void reset();
  void initDialogue(List<P<DialogueLine>> dialogueLines, String prefix, P<TextFieldController> tf_a, Vector3 color_a, P<TextFieldController> tf_b = nullptr, Vector3 color_b = /*default: default(Vector3)*/{}, P<TextFieldController> tf_c = nullptr, Vector3 color_c = /*default: default(Vector3)*/{}, P<Sprite> background = nullptr);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
