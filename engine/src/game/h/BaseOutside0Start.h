// Generated from BaseOutside0Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseOutside0Start.cpp
#pragma once
#include "../game_types.h"

class BaseOutside0Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> spider1{};
  P<SpriteRenderer> spider2{};
  P<SpriteRenderer> bugs{};
  P<SpriteRenderer> piorunochron{};
  P<SpriteRenderer> snow{};
  // ---- constructors
  BaseOutside0Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
