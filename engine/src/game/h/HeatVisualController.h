// Generated from HeatVisualController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HeatVisualController.cpp
#pragma once
#include "../game_types.h"

class HeatVisualController : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> s1{};
  P<Sprite> s2{};
  P<Sprite> s3{};
  P<Sprite> s4{};
  P<Sprite> s5{};
  float alfa = 1.0f;
  float delay{};
  int lastran{};
  // ---- constructors
  HeatVisualController() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
