// Generated from ResultsChapterCold.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterCold.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterCold : public ResultsController {
public:
  // ---- fields
  String analytics_basket = S("?");
  String analytics_doors = S("?");
  String analytics_electric = S("?");
  String analytics_fireplace = S("?");
  String analytics_gas = S("?");
  String analytics_gear = S("?");
  String analytics_cooler = S("?");
  String analytics_oven = S("?");
  String analytics_stayed = S("?");
  // ---- constructors
  ResultsChapterCold() {}
  // ---- methods
  int checkWindows(P<TimelineAction> tla, String name1, String name2, int value1);
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
