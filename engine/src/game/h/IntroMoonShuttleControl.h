// Generated from IntroMoonShuttleControl.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/IntroMoonShuttleControl.cpp
#pragma once
#include "../game_types.h"

class IntroMoonShuttleControl : public MonoBehaviour {
public:
  // ---- fields
  P<ParticleGenerator> d1{};
  P<ParticleGenerator> d2{};
  P<ParticleGenerator> d3{};
  P<ParticleGenerator> d4{};
  P<ParticleGenerator> d5{};
  P<ParticleGenerator> d6{};
  P<AudioSource> aS{};
  // ---- constructors
  IntroMoonShuttleControl() {}
  // ---- methods
  void Start();
  void Update();
  void enableBackDust();
  void enableBackDust2();
  void enablefrontDust();
  void disableBackDust();
  void disablefrontDust();
  void startSound();
  void startSound2();
  void soundBum();
  void soundPisk();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
