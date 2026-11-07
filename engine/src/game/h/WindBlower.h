// Generated from WindBlower.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/WindBlower.cpp
#pragma once
#include "../game_types.h"

class WindBlower : public MonoBehaviour {
public:
  // ---- fields
  static float globalSpeedX;
  static float globalSpeedY;
  float targetSpeedX{};
  float targetSpeedY{};
  float deltaX = 0.1f;
  float deltaY = 0.1f;
  int currentDelta{};
  int delta{};
  int maxDelta = 300;
  int minDelta = 100;
  float maxSpeedX{};
  float maxSpeedY{};
  float minSpeedX{};
  float minSpeedY{};
  // ---- constructors
  WindBlower() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
