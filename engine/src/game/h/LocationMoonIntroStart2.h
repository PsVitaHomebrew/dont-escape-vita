// Generated from LocationMoonIntroStart2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonIntroStart2.cpp
#pragma once
#include "../game_types.h"

class LocationMoonIntroStart2 : public MonoBehaviour {
public:
  // ---- fields
  List<float> realX{};
  List<float> speed{};
  List<float> target{};
  P<GameObject> shuttle{};
  P<GameObject> shuttleShadow{};
  List<P<GameObject>> layer{};
  P<GameObject> bruzda{};
  float speedMod{};
  bool transition{};
  float realFakePlayerX{};
  float animProgress0{};
  float animProgress1{};
  float animProgress2{};
  float animProgress3{};
  float animProgress4{};
  float animProgress25{};
  float ambientVol = 1.0f;
  P<ParticleGenerator> dust{};
  P<ParticleGenerator> dust2{};
  P<ParticleGenerator> dust3{};
  P<ParticleGenerator> dust4{};
  bool landed{};
  bool crashed{};
  bool stopping{};
  bool jetStarted{};
  P<AudioSource> aS{};
  // ---- constructors
  LocationMoonIntroStart2() {}
  // ---- methods
  void Start();
  void robSypuSypu();
  void Update();
  void nextScene();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
