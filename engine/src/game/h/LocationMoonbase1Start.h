// Generated from LocationMoonbase1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonbase1Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoonbase1Start : public MonoBehaviour {
public:
  // ---- fields
  float time{};
  float destructionProgress0{};
  float destructionProgress1{};
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
  List<P<ParticleGenerator>> sparkles{};
  List<float> times{};
  bool sparkstime{};
  int destIndex0{};
  int destIndex1{};
  int destIndex2{};
  P<SpriteRenderer> suit_david{};
  P<SpriteRenderer> suit_cate{};
  P<SpriteRenderer> suit_barry{};
  P<SpriteRenderer> suit_cody{};
  P<LocationManager> lm{};
  bool startdestruction1{};
  bool startdestruction2{};
  P<AudioSource> audioSource2{};
  P<AudioSource> audioSource3{};
  // ---- constructors
  LocationMoonbase1Start() {}
  // ---- methods
  void Start();
  void getnote(String s = S(""));
  void unlock();
  void sparkles1();
  void sparkles2();
  void sparkles3();
  void sparkles4();
  void sparkles5();
  void sparkles6();
  void removeSuits(String val = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
