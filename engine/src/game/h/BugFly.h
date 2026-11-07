// Generated from BugFly.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BugFly.cpp
#pragma once
#include "../game_types.h"

class BugFly : public MonoBehaviour {
public:
  // ---- fields
  float speedModX{};
  float speedModY{};
  float targetSpeedModX{};
  float targetSpeedModY{};
  Vector2 speed{};
  Vector4 bounds{};
  bool started{};
  Vector3 pos{};
  // ---- constructors
  BugFly() {}
  // ---- methods
  void Start();
  void startFly(int i);
  void startFly2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
