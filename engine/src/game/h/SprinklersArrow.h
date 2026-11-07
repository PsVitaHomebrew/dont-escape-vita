// Generated from SprinklersArrow.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SprinklersArrow.cpp
#pragma once
#include "../game_types.h"

class SprinklersArrow : public MonoBehaviour {
public:
  // ---- fields
  Array<P<Sprite>> arrows{};
  int delay{};
  int maxDelay = 8;
  int currentDisplay{};
  int maxDisplay = 16;
  P<SpriteRenderer> sr{};
  bool fastUpdate = true;
  // ---- constructors
  SprinklersArrow() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
