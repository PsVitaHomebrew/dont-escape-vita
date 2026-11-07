// Generated from JournalTexts.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/JournalTexts.cpp
#pragma once
#include "../game_types.h"

class JournalTexts : public MonoBehaviour {
public:
  // ---- fields
  static String textToType;
  static String textToType2;
  static List<P<Objective>> journalTimeItems;
  static P<JournalButtonController> jbc;
  // ---- constructors
  JournalTexts() {}
  // ---- methods
  void Start();
  void Update();
  static bool anotherText(String condition, String text);
  static int findOldestJournalEntry();
  static bool anotherText(bool condition, String text, String text2);
  static String pickTexts(int chapter, bool updateNumber = false);
  static String chapter4Texts();
  static String chapter3Texts();
  static String chapter2Texts();
  static String chapter1Texts();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
