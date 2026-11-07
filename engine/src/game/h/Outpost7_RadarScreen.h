// Generated from Outpost7_RadarScreen.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost7_RadarScreen.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost7_RadarScreen : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> radar_background{};
  P<SpriteRenderer> radar_dot{};
  P<SpriteRenderer> radar_swipe1{};
  P<SpriteRenderer> radar_swipe2{};
  P<AudioSource> aS{};
  // ---- constructors
  Outpost7_RadarScreen() {}
  // ---- methods
  void Start();
  void turn(String s = S(""));
  void talkAboutRadarOnPlaneOn();
  void talkAboutRadarOnPlaneOff();
  void talkAboutRadarOff();
  void clickAction() override;
  void endView(String var = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
