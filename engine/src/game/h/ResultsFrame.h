// Generated from ResultsFrame.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsFrame.cpp
#pragma once
#include "../game_types.h"

class ResultsFrame : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<SpriteRenderer> frame{};
  float targetAlpha{};
  float alpha{};
  P<Sprite> nextSprite{};
  // ---- constructors
  ResultsFrame() {}
  // ---- methods
  void Start();
  void move(float x, float y);
  void Update();
  void show(P<Sprite> sprite);
  void hide();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
