// Generated from ResultsChapterBugs.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterBugs.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterBugs : public ResultsController {
public:
  // ---- fields
  String analytics_stayed = S("?");
  String analytics_doors = S("0");
  String analytics_window_1 = S("0");
  String analytics_window_2 = S("0");
  String analytics_window_3 = S("0");
  String analytics_pest = S("false");
  String analytics_sonic = S("0");
  String analytics_sprinklers = S("false");
  String analytics_weapon = S("?");
  // ---- constructors
  ResultsChapterBugs() {}
  // ---- methods
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
