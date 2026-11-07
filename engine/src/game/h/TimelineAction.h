// Generated from TimelineAction.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TimelineAction.cpp
#pragma once
#include "../game_types.h"

class TimelineAction : public Obj {
public:
  // ---- fields
  float time{};
  float textTime{};
  P<TextFieldController> textfield{};
  String text{};
  int textWidth = -1;
  bool blockG = true;
  bool fast{};
  bool instant{};
  Vector3 textColor = Vector3(1.0f, 1.0f, 1.0f);
  Vector3 backgroundColor = Vector3(0.0f, 0.0f, 0.0f);
  float backgroundAlpha = 0.75f;
  TimelineFunction function{};
  String param = String(u"");
  bool actionWithText{};
  bool textDisplayed{};
  // ---- constructors
  TimelineAction(P<TextFieldController> tf = nullptr);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
