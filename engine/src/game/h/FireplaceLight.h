// Generated from FireplaceLight.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/FireplaceLight.cpp
#pragma once
#include "../game_types.h"

class FireplaceLight : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> fireLight{};
  // ---- constructors
  FireplaceLight() {}
  // ---- methods
  void Start();
  void Update();
  void newShadow();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
