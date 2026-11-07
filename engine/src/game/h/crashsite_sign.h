// Generated from crashsite_sign.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/crashsite_sign.cpp
#pragma once
#include "../game_types.h"

class crashsite_sign : public MonoBehaviour {
public:
  // ---- constructors
  crashsite_sign() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
