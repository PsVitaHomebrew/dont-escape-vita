// Generated from Crashsite1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Crashsite1Start.cpp
#pragma once
#include "../game_types.h"

class Crashsite1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> tloD1{};
  P<SpriteRenderer> tloD2{};
  // ---- constructors
  Crashsite1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
