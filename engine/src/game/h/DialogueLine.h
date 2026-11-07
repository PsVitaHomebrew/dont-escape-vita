// Generated from DialogueLine.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DialogueLine.cpp
#pragma once
#include "../game_types.h"

class DialogueLine : public Obj {
public:
  // ---- fields
  P<TextFieldController> source{};
  Vector3 textColor{};
  String text{};
  TimelineFunction action{};
  String actionParam = String(u"");
  bool actionWithText{};
  bool displayText{};
  float time{};
  // ---- constructors
  DialogueLine();
  DialogueLine(P<TextFieldController> src, Vector3 tC, String t, TimelineFunction a, bool awt = false, bool dt = true, float tim = 0.0f);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
