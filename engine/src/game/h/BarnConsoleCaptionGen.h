// Generated from BarnConsoleCaptionGen.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnConsoleCaptionGen.cpp
#pragma once
#include "../game_types.h"

class BarnConsoleCaptionGen : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  P<TextFieldController> t{};
  // ---- constructors
  BarnConsoleCaptionGen() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
