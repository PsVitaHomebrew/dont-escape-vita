// Generated from CraneThing.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CraneThing.cpp
#pragma once
#include "../game_types.h"

class CraneThing : public MonoBehaviour {
public:
  // ---- fields
  float targetX = 120.0f;
  float targetY = 120.0f;
  float currentX = 220.0f;
  float currentY = 80.0f;
  P<Sprite> closed{};
  P<Sprite> open{};
  float yyy = 20.0f;
  P<GameObject> metal{};
  // ---- constructors
  CraneThing() {}
  // ---- methods
  void Start();
  void updateState();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
