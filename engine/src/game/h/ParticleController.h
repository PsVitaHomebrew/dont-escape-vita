// Generated from ParticleController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ParticleController.cpp
#pragma once
#include "../game_types.h"

class ParticleController : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spriteR{};
  float alpha{};
  int speedXMin{};
  int speedXMax{};
  int speedYMin{};
  int speedYMax{};
  int lifetime{};
  float fadeInStep = 0.1f;
  float fadeOutStep = 0.1f;
  int currentSpeedX{};
  int currentSpeedY{};
  float minAlpha{};
  float maxAlpha{};
  float targetAlpha{};
  float currentLifetime{};
  Vector2 currentXY{};
  float speedDiv = 10.0f;
  bool globalized = true;
  bool die{};
  float takeItEasy{};
  // ---- constructors
  ParticleController() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
