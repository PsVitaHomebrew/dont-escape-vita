// Generated from CrossroadStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CrossroadStart.cpp
#pragma once
#include "../game_types.h"

class CrossroadStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> heli{};
  P<SpriteRenderer> snow{};
  P<SpriteRenderer> roof{};
  P<SpriteRenderer> ditches{};
  // ---- constructors
  CrossroadStart() {}
  // ---- methods
  void Start();
  void walkThere1();
  void walkThere();
  void unlock();
  void showIntro1();
  void showIntro2();
  void showIntro1b();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
