// Generated from ResultsChapterHot.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterHot.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterHot : public ResultsController {
public:
  // ---- fields
  String analytics_ac = S("?");
  String analytics_cooler = S("?");
  String analytics_doors = S("?");
  String analytics_fan = S("?");
  String analytics_gear = S("?");
  String analytics_oven = S("?");
  String analytics_stayed = S("?");
  // ---- constructors
  ResultsChapterHot() {}
  // ---- methods
  int checkWindows(P<TimelineAction> tla, String name1, String name2, int value1);
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
