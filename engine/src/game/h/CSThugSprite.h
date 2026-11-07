// Generated from CSThugSprite.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CSThugSprite.cpp
#pragma once
#include "../game_types.h"

class CSThugSprite : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  P<LocationCS2Start> cs2{};
  // ---- constructors
  CSThugSprite() {}
  // ---- methods
  void Start();
  void Update();
  void hide();
  void show();
  void getShot();
  void shoot();
  void distracted();
  void distractedEnd();
  void reset();
  void myk();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
