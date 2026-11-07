// Generated from ResultsChapterSpiders.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterSpiders.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterSpiders : public ResultsController {
public:
  // ---- fields
  String analytics_stayed = S("?");
  String analytics_doors = S("?");
  String analytics_weapon = S("?");
  String analytics_repel = S("?");
  String analytics_sprinklers = S("?");
  String analytics_traps = S("?");
  String analytics_window_1 = S("?");
  String analytics_window_2 = S("?");
  String analytics_window_3 = S("?");
  // ---- constructors
  ResultsChapterSpiders() {}
  // ---- methods
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
