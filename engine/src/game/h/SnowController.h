// Generated from SnowController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SnowController.cpp
#pragma once
#include "../game_types.h"

class SnowController : public MonoBehaviour {
public:
  // ---- fields
  P<ParticleGenerator> s1{};
  P<ParticleGenerator> s2{};
  P<ParticleGenerator> s3{};
  // ---- constructors
  SnowController() {}
  // ---- methods
  void Start();
  void snowRangeYChange();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
