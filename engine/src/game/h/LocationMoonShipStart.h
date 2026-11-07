// Generated from LocationMoonShipStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonShipStart.cpp
#pragma once
#include "../game_types.h"

class LocationMoonShipStart : public MonoBehaviour {
public:
  // ---- fields
  List<P<ParticleGenerator>> sparks{};
  List<float> times{};
  P<AudioSource> audioSouruce{};
  P<AudioSource> audioSource2{};
  P<AudioSource> audioSource3{};
  P<AudioSource> rumbler{};
  float time{};
  // ---- constructors
  LocationMoonShipStart() {}
  // ---- methods
  void Start();
  void updateThings();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
