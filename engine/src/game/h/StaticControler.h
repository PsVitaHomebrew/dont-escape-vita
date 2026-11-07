// Generated from StaticControler.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/StaticControler.cpp
#pragma once
#include "../game_types.h"

class StaticControler : public MonoBehaviour {
public:
  // ---- fields
  Vector3 vvv{};
  Vector3 pos{};
  P<Sprite> sprite{};
  P<SpriteRenderer> spriteRenderer{};
  static int static_power;
  float time{};
  // ---- constructors
  StaticControler() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
