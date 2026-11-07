// Generated from ResultsChapterStorm.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterStorm.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterStorm : public ResultsController {
public:
  // ---- fields
  String analytics_stayed = String(u"");
  String analytics_sarge_status = S("neutral");
  String analytics_ammo_sabotaged = S("false");
  String analytics_doors_and_windows = S("?");
  String analytics_food_poisoned = S("false");
  String analytics_guard_killed = S("false");
  String analytics_traps = S("0/4");
  String analytics_weapon = S("none");
  String analytics_whiskey_dumped = S("false");
  // ---- constructors
  ResultsChapterStorm() {}
  // ---- methods
  int checkTrap(String trapname);
  int checkWindows(P<TimelineAction> tla, String name1, String name2, int value1);
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
