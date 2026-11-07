// Generated from CS1_Waypoint_2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS1_Waypoint_2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS1_Waypoint_2 : public ObjectActionController {
public:
  // ---- constructors
  CS1_Waypoint_2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void goThere(String s = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
