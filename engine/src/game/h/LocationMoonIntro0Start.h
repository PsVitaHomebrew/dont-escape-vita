// Generated from LocationMoonIntro0Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonIntro0Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoonIntro0Start : public MonoBehaviour {
public:
  // ---- fields
  List<float> realY{};
  List<float> speed{};
  List<float> target{};
  P<GameObject> shuttle{};
  List<P<GameObject>> layer{};
  float speedMod{};
  float animProgress0{};
  float animProgress1{};
  float ambientVol = 1.0f;
  P<ParticleGenerator> dust{};
  P<ParticleGenerator> dust2{};
  P<ParticleGenerator> dust3{};
  P<ParticleGenerator> dust4{};
  bool landing{};
  bool jetStarted{};
  bool transitioning{};
  P<AudioSource> aS{};
  // ---- constructors
  LocationMoonIntro0Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
