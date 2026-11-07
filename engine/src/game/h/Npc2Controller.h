// Generated from Npc2Controller.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Npc2Controller.cpp
#pragma once
#include "../game_types.h"
#include "NPCActionController.h"

class Npc2Controller : public NPCActionController {
public:
  // ---- fields
  bool struggled{};
  static Vector3 color;
  // ---- constructors
  Npc2Controller() {}
  // ---- methods
  static Vector3 getColor();
  void continueStart() override;
  void whatOnClick() override;
  void whatOnClick0() override;
  void giveNote(String val = S(""));
  void siderealFall();
  void fallAccelerate();
  void giveLocket();
  void standUp(String val = S(""));
  void fall(String val = S(""));
  void sit_strugle1();
  void sit_strugle(String val = S(""));
  void drawGun(String val = S(""));
  void aimGun(String val = S(""));
  void read(String val = S(""));
  void read2(String val = S(""));
  void read3(String val = S(""));
  void returnToSpawn(String val = S(""));
  void sitDown(String val = S(""));
  void goToSleep1(String a = S(""));
  void goToSleep2(String a = S(""));
  void goToSleep3();
  void closePod(String s = S(""));
  void pod_rotate();
  void pod_rotate2();
  void playerStandUp(String v = S(""));
  void npcClickAction(String item = S("")) override;
  void dialogues();
  void goAndWait(String param = S(""));
  void stopWalking();
  void clickAction2() override;
  void updateState() override;
  void clickAction0() override;
  void upgradeCarQuestion(String val = S(""));
  void upgradeCar();
  void sayUpgraded();
  void pushPipe(String val = S(""));
  void pushTrashCart(String val = S(""));
  void pushTrashCart2();
  void pushTrashCartSound();
  void goToGrave(String val = S(""));
  void endTalkRoof(String val = S(""));
  void endTalkShip(String val = S(""));
  void gingerFacepalm(String val = S(""));
  void lookUp(String val = S(""));
  void openGarage(String val = S(""));
  void openGarage2();
  void closeGarage();
  void uratuj();
  void naChama();
  void barrySaved();
  void barrySaved2();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
