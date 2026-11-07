// Generated from Timeline.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Timeline.cpp
#pragma once
#include "../game_types.h"

class Timeline : public MonoBehaviour {
public:
  // ---- fields
  static P<Timeline> t;
  P<TextFieldController> textField{};
  List<P<TimelineAction>> actions{};
  static int defaultTwidth;
  bool doNotUnlock{};
  // ---- constructors
  Timeline() {}
  // ---- methods
  void Awake();
  void stopChitChat();
  bool isSafeToChangeBusy();
  void addAction(P<TimelineAction> action);
  void addDialogueLines(List<P<DialogueLine>> dl);
  void addDialogue(P<DialogueLine> dl, float tTime = 0.0f);
  void initTextfield();
  void Start();
  void Update();
  void functionLaunch();
  void proceedWithPurpose();
  void killText();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
