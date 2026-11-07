// Generated from Npc3Controller.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Npc3Controller.cpp
#pragma once
#include "../game_types.h"
#include "NPCActionController.h"

class Npc3Controller : public NPCActionController {
public:
  // ---- fields
  static Vector3 color; // = new Vector3(390f / 1024f, 0.5683594f, 330f / 1024f)  (set in _cctor)
  // ---- constructors
  Npc3Controller() {}
  // ---- methods
  static Vector3 getColor();
  void continueStart() override;
  void giveFoodCan(String val = S(""));
  void giveBackFoodCan(String val = S(""));
  void giveFoodCanOpen(String val = S(""));
  void whatOnClick0() override;
  void whatOnClick() override;
  void uratuj();
  void naChama();
  void codySaved();
  void codySaved2();
  void siderealFall();
  void fallAccelerate();
  void endTalkRoof(String val = S(""));
  void endTalkShip(String val = S(""));
  void playerStandUp(String v = S(""));
  void npcClickAction(String item = S("")) override;
  void revolverQuestion(String s = S(""));
  void revolverTeach();
  void revolverDone();
  void goToSleep1(String a = S(""));
  void goToSleep2(String a = S(""));
  void goToSleep3();
  void closePod(String s = S(""));
  void pod_rotate();
  void pod_rotate2();
  void dialogues();
  void goAndWait(String param = S(""));
  void stopWalking();
  void startTalkRestaurant(String val = S(""));
  void endTalkRestaurant(String val = S(""));
  void endTalkRestaurant2(String val = S(""));
  void flip();
  void clickAction2() override;
  void updateState() override;
  void clickAction0() override;
  void goVent1(String val = S(""));
  void goVent(String val = S(""));
  void fightStance(String val = S(""));
  void openDoorSound();
  // ---- generated
  static void _cctor(); // translator: set the static fields marked (set in _cctor)
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
