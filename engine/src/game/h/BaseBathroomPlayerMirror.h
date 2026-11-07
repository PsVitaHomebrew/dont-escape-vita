// Generated from BaseBathroomPlayerMirror.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseBathroomPlayerMirror.cpp
#pragma once
#include "../game_types.h"

class BaseBathroomPlayerMirror : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spriteRenderer{};
  P<SpriteRenderer> playerSprite{};
  // ---- constructors
  BaseBathroomPlayerMirror() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
