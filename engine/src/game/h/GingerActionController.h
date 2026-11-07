// Generated from GingerActionController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GingerActionController.cpp
#pragma once
#include "../game_types.h"
#include "NPCActionController.h"

class GingerActionController : public NPCActionController {
public:
  // ---- fields
  static Vector3 color; // = new Vector3(215f / 255f, 58f / 255f, 46f / 255f)  (set in _cctor)
  P<TextFieldController> distractBarryTextfield{};
  // ---- constructors
  GingerActionController() {}
  // ---- methods
  static Vector3 getColor();
  static bool isGingerHere();
  void continueStart() override;
  void whatOnClick() override;
  void whatOnClick0() override;
  void playerStandUp(String v = S(""));
  void endTalkShip(String val = S(""));
  void roofAfterFall();
  void goToSleep1(String a = S(""));
  void goToSleep2(String a = S(""));
  void goToSleep3();
  void closePod(String s = S(""));
  void pod_rotate();
  void pod_rotate2();
  void roofWalkAway(String a = S(""));
  void roofWalkAway2();
  void npcClickAction(String item = S("")) override;
  void dialogues();
  void fingerPress(String val = S(""));
  void firstEndTalk(String val = S(""));
  void clickAction2() override;
  void updateState() override;
  void clickAction0() override;
  void goDistractBarry(String val = S(""));
  void showMap(String val = S(""));
  void resumeAfterMap();
  void drawGun(String val = S(""));
  void aimGun(String val = S(""));
  void holdGunUp(String val = S(""));
  void aimDown(String val = S(""));
  void holster(String val = S(""));
  void openThePodBayDoors(String a = S(""));
  void killRazor(String a = S(""));
  void spareRazor(String a = S(""));
  void evaluateRazor(String a = S(""));
  void mourn();
  void mourned(String t = S(""));
  void pushTrashCart(String val = S(""));
  void pushTrashCart2();
  void pushTrashCartSound();
  void distractBarry1();
  void distractBarry();
  void unlockDistraction(String val = S(""));
  void setDistractFalse(String val = S(""));
  void distractBarryEnd();
  void initFindShipDialogue();
  // ---- generated
  static void _cctor(); // translator: set the static fields marked (set in _cctor)
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
