// Generated from ResultsController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsController.cpp
#pragma once
#include "../game_types.h"

class ResultsController : public MonoBehaviour {
public:
  // ---- fields
  int winQuality{};
  int danger{};
  int surviavbleDanger{};
  int removeDanger{};
  P<ProgressBarController> pbc{};
  P<ResultsFrame> rf{};
  // ---- constructors
  ResultsController() {}
  // ---- methods
  void Start();
  void Update();
  void init();
  void skipFast(String val = S(""));
  int check(int danger = 0, String label = S(""), String pic = S(""), bool trackWasShortened = true);
  void liveOrDie2(String val = S(""));
  void liveOrDie(String val = S(""));
  void changeDanger(String val = S(""));
  virtual void chapterResult();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
