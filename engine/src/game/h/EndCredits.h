// Generated from EndCredits.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/EndCredits.cpp
#pragma once
#include "../game_types.h"

class EndCredits : public MonoBehaviour {
public:
  // ---- constructors
  EndCredits() {}
  // ---- methods
  void Start();
  void Update();
  void hide();
  void showDontEscape();
  void showBlack();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
