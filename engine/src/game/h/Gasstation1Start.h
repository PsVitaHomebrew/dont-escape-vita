// Generated from Gasstation1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Gasstation1Start.cpp
#pragma once
#include "../game_types.h"

class Gasstation1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> spiders1{};
  P<Sprite> spiders2{};
  P<TextFieldController> tf1{};
  P<TextFieldController> tf2{};
  Vector3 color1{};
  Vector3 color2{};
  P<TextFieldController> tf{};
  Vector3 color{};
  // ---- constructors
  Gasstation1Start() {}
  // ---- methods
  void Start();
  void thugTalk();
  void spiderAttack();
  void spiderAttack2();
  void spiderAttack2b();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
