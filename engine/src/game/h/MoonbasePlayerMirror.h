// Generated from MoonbasePlayerMirror.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MoonbasePlayerMirror.cpp
#pragma once
#include "../game_types.h"

class MoonbasePlayerMirror : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spriteRenderer{};
  P<SpriteRenderer> playerSprite{};
  String objectName{};
  bool doIEvenCare{};
  // ---- constructors
  MoonbasePlayerMirror() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
