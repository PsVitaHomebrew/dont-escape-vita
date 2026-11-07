// Generated from LocationMoonbase2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonbase2Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoonbase2Start : public MonoBehaviour {
public:
  // ---- fields
  float time{};
  float destructionProgress{};
  float destructionProgress2{};
  float cloudProgress1{};
  float cloudProgress2{};
  P<AudioSource> audioSouruce{};
  P<AudioSource> rumbler{};
  float secToSave{};
  List<P<GameObject>> kawalkiKsiezyca{};
  P<GameObject> chmura1{};
  P<GameObject> chmura2{};
  P<GameObject> earth{};
  P<GameObject> moon_shadow{};
  List<float> kawalkiFinish{};
  P<ParticleGenerator> pg1{};
  P<ParticleGenerator> pg2{};
  P<ParticleGenerator> pg3{};
  P<ParticleGenerator> pg4{};
  int destIndex1{};
  int destIndex2{};
  bool startdestruction1{};
  bool startdestruction2{};
  bool windowMayCrack{};
  // ---- constructors
  LocationMoonbase2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
