// Generated from Waypoint_Crashsite2_Pesttruck.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Crashsite2_Pesttruck.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Crashsite2_Pesttruck : public ObjectActionController {
public:
  // ---- constructors
  Waypoint_Crashsite2_Pesttruck() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void whatOnClick() override;
  void yesClicked();
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
