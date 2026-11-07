// Generated from MoonbaseLightFlicker.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MoonbaseLightFlicker.cpp
#pragma once
#include "../game_types.h"

class MoonbaseLightFlicker : public MonoBehaviour {
public:
  // ---- fields
  P<LocationManager> lm{};
  P<SpriteRenderer> lights{};
  P<SpriteRenderer> darkness{};
  P<SpriteRenderer> darkness2{};
  P<NPCWalkController> cody{};
  P<NPCWalkController> barry{};
  P<NPCWalkController> cate{};
  float time1{};
  float time2{};
  P<SpriteRenderer> moreObjects1{};
  P<SpriteRenderer> moreObjects2{};
  P<SpriteRenderer> moreObjects3{};
  P<SpriteRenderer> moreObjects4{};
  P<SpriteRenderer> moreObjects5{};
  bool lightsFailed{};
  // ---- constructors
  MoonbaseLightFlicker() {}
  // ---- methods
  void Start();
  void Update();
  void charLights();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
