// Generated from ClockController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ClockController.cpp
#pragma once
#include "../game_types.h"

class ClockController : public MonoBehaviour {
public:
  // ---- fields
  String frame_name_sufix{};
  String sufix_minutes{};
  String sufix_hours{};
  int equip_i{};
  P<GameObject> minutesHand{};
  P<GameObject> hoursHand{};
  P<SpriteRenderer> spriteRenderer1{};
  P<SpriteRenderer> spriteRenderer2{};
  P<SpriteRenderer> spriteRenderer3{};
  P<Sprite> invEquip{};
  P<Sprite> waitBcg{};
  P<DialogueOptionController> doc{};
  // ---- constructors
  ClockController() {}
  // ---- methods
  void Start();
  void showClock(String param = S(""));
  void showFinal();
  void show();
  void hide();
  static String getClockTimeWithRemaining();
  static Vector3 getTimeColor();
  static bool advanceTime(int amount, bool traveling = false);
  static void endTime(bool accident = false);
  static String getClockTime(int timeToTranslate = -1);
  static String getTimeLeft();
  void Update();
  void OnMouseOver();
  void OnMouseExit();
  void hideText();
  void takeDoc(int i);
  void endTalk(String val = S(""));
  void equipItem(String item);
  void OnMouseDown();
  void showEndDialogue(String s = S("clock_click"), String s2 = S("equip_nothing"));
  void addItem(String item, String how);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
