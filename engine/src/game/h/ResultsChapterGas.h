// Generated from ResultsChapterGas.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterGas.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterGas : public ResultsController {
public:
  // ---- fields
  String analytics_doors = S("open");
  String analytics_floor = S("?");
  String analytics_sprinklers = S("false");
  String analytics_stayed = S("?");
  String analytics_chemichal = S("?");
  String analytics_gear = S("?");
  String analytics_window_1 = S("?");
  String analytics_window_2 = S("?");
  String analytics_window_3 = S("?");
  // ---- constructors
  ResultsChapterGas() {}
  // ---- methods
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
