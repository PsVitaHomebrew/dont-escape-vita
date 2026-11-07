// Generated from CS3ThugSprite.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS3ThugSprite.cpp
#pragma once
#include "../game_types.h"

class CS3ThugSprite : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteShadow> shadow{};
  int shadowOffsetY{};
  bool thisOneCanBeShot{};
  // ---- constructors
  CS3ThugSprite() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
