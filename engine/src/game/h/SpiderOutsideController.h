// Generated from SpiderOutsideController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SpiderOutsideController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SpiderOutsideController : public ObjectActionController {
public:
  // ---- fields
  float realX = 0.023f;
  bool peopleShottingAtUs{};
  bool runLikeHell{};
  // ---- constructors
  SpiderOutsideController() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void showClock();
  void whatOnClick() override;
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void hitAndRun();
  void hiss();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
