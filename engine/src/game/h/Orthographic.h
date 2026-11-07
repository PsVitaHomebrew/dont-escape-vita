// Generated from Orthographic.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Orthographic.cpp
#pragma once
#include "../game_types.h"

class Orthographic : public MonoBehaviour {
public:
  // ---- fields
  float offset{};
  // ---- constructors
  Orthographic() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
