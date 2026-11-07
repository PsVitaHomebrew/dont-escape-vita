// Generated from OutpostBarsPuzzleCaption_Title.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostBarsPuzzleCaption_Title.cpp
#pragma once
#include "../game_types.h"

class OutpostBarsPuzzleCaption_Title : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  P<TextFieldController> t{};
  // ---- constructors
  OutpostBarsPuzzleCaption_Title() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
