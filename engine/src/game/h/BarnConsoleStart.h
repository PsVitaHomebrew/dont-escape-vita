// Generated from BarnConsoleStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnConsoleStart.cpp
#pragma once
#include "../game_types.h"

class BarnConsoleStart : public MonoBehaviour {
public:
  // ---- constructors
  BarnConsoleStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
