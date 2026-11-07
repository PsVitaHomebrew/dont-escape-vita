// Generated from LocationDream3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDream3Start.cpp
#pragma once
#include "../game_types.h"

class LocationDream3Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> plane0bla{};
  P<SpriteRenderer> plane01{};
  P<SpriteRenderer> window{};
  P<SpriteRenderer> hot{};
  P<SpriteRenderer> cold{};
  P<SpriteRenderer> stairs{};
  float alpha{};
  float alpha1{};
  float alpha2{};
  // ---- constructors
  LocationDream3Start() {}
  // ---- methods
  void Start();
  void walkThere1();
  void walkThere();
  void unlock();
  void unlockThings(String param);
  void unlockThings3(String param);
  void unlockThings2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
