// Generated from BaseOutside2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseOutside2Start.cpp
#pragma once
#include "../game_types.h"

class BaseOutside2Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spider1{};
  P<SpriteRenderer> spider2{};
  P<PolygonCollider2D> graveBlock1{};
  P<PolygonCollider2D> graveBlock2{};
  P<SpriteRenderer> bugs{};
  P<SpriteRenderer> snow{};
  // ---- constructors
  BaseOutside2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
