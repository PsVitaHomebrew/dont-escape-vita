// Generated from NPCActionController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/NPCActionController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class NPCActionController : public ObjectActionController {
public:
  // ---- fields
  P<Item> itemRef{};
  P<DialogueOptionController> doc{};
  List<P<DialogueLine>> instantLines{};
  P<TextFieldController> textField{};
  List<P<DialogueLine>> randomLines{};
  float randomLinesProbab{};
  bool busyTalkingRandomly{};
  bool rotateToSpeaker = true;
  int delay{};
  int frame{};
  P<GameObject> inventory{};
  // ---- constructors
  NPCActionController() {}
  // ---- methods
  void Awake();
  void setFlippedL();
  void setFlippedR();
  int locationDialogue(int i, Vector3 color, String who);
  int dayDialogue(int i, Vector3 color, String who);
  void decideRandomTopic();
  void randomLinesTalkOrNot(bool force = false);
  void makeNotBusy(String v = S(""));
  void init(P<Item> item);
  void Update();
  void takeDoc(int i);
  void OnEnable();
  void Start();
  void whatOnClick() override;
  void clickAction() override;
  void endTalk(String val = S(""));
  virtual void npcClickAction(String item = S(""));
  virtual void continueStart();
  void clickAction2() override;
  void updateState() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
