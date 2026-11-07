// Generated from lightingblast.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/lightingblast.cpp
#pragma once
#include "../game_types.h"

class lightingblast : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> light{};
  P<AudioSource> aS{};
  float prelight{};
  bool postlight{};
  float maxAlpha{};
  float autoblastDelay = -111.0f;
  // ---- constructors
  lightingblast() {}
  // ---- methods
  void Start();
  void initthis();
  void strike(P<AudioClip> thunder, float pre, bool post, float vol = 1.0f, float ma = 0.5f);
  void startAutoBlast();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
