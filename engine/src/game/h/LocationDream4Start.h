// Generated from LocationDream4Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDream4Start.cpp
#pragma once
#include "../game_types.h"

class LocationDream4Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> plane0bla{};
  P<SpriteRenderer> plane01{};
  P<SpriteRenderer> window{};
  P<SpriteRenderer> hot{};
  P<SpriteRenderer> cold{};
  P<SpriteRenderer> door{};
  float alpha{};
  float alpha1{};
  float alpha2{};
  P<SpriteRenderer> moon1{};
  P<SpriteRenderer> moon2{};
  P<SpriteRenderer> moon3{};
  P<SpriteRenderer> meteor1{};
  P<SpriteRenderer> meteor2{};
  float animationProgress0 = -1.0f;
  float animationProgress{};
  float animationProgress2{};
  float animationProgress3{};
  // ---- constructors
  LocationDream4Start() {}
  // ---- methods
  void Start();
  void walkThere1();
  void walkThere();
  void unlock();
  void unlockThings(String param);
  void unlockThings2();
  void fallMoon();
  void rumble();
  void nextscene();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
