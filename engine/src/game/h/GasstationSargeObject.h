// Generated from GasstationSargeObject.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationSargeObject.cpp
#pragma once
#include "../game_types.h"
#include "NPCActionController.h"

class GasstationSargeObject : public NPCActionController {
public:
  // ---- fields
  P<GasstationSarge> sarge{};
  static Vector3 color;
  P<GameObject> am1{};
  P<GameObject> am2{};
  // ---- constructors
  GasstationSargeObject() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick0() override;
  void stopAim(String a = S(""));
  void getToWork(String a = S(""));
  void stopWork(String a = S(""));
  void shootHim();
  void shootHim2();
  void shootHim3();
  void initIntroDialogue();
  void dialogues();
  void endTalk1(String val = S(""));
  void clickAction() override;
  void endWrench(String a = S(""));
  void farewell(String a = S(""));
  void hideBike();
  void doneFuel();
  void puke(String aaa = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void dontTouchThat();
  void talkWrench();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
