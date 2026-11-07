// Generated from BottomTextController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BottomTextController.cpp
#pragma once
#include "../game_types.h"

class BottomTextController : public MonoBehaviour {
public:
  // ---- fields
  static int bottomTextWidth;
  // ---- constructors
  BottomTextController() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
