// Generated from SpiderFall.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SpiderFall.cpp
#pragma once
#include "../game_types.h"

class SpiderFall : public MonoBehaviour {
public:
  // ---- fields
  float speedX{};
  float speedY{};
  float targetY = -0.35f;
  float targetX = 0.487f;
  bool started{};
  int iii{};
  int delay{};
  Vector3 pos{};
  // ---- constructors
  SpiderFall() {}
  // ---- methods
  void Start();
  void startFall();
  void startFall2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
