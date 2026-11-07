// Generated from ParticleGenerator.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ParticleGenerator.cpp
#pragma once
#include "../game_types.h"

class ParticleGenerator : public MonoBehaviour {
public:
  // ---- fields
  int maxParticles{};
  int minDelayBetweeenParticles{};
  int maxDelayBetweeenParticles{};
  int speedXMin{};
  int speedXMax{};
  int speedYMin{};
  int speedYMax{};
  int lifetimeMin{};
  int lifetimeMax{};
  float fadeInStep = 0.1f;
  float fadeOutStep = 0.1f;
  float minAlpha = 1.0f;
  float maxAlpha = 1.0f;
  List<P<GameObject>> particles{};
  float currentDelay{};
  int delay{};
  float zShift{};
  int xSpread{};
  int ySpread{};
  int xStart{};
  int yStart{};
  float speedDiv{};
  bool useGlobalWind = true;
  Array<P<Sprite>> sprites{};
  bool glow{};
  int index{};
  bool started = true;
  // ---- constructors
  ParticleGenerator() {}
  // ---- methods
  void Start();
  void Update();
  void removeParticles();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
