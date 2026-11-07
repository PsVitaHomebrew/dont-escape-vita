// Generated from LocationAttic2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAttic2Start.cpp
#pragma once
#include "../game_types.h"

class LocationAttic2Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> destroyed{};
  P<SpriteRenderer> shadow{};
  P<SpriteRenderer> shadow2{};
  P<SpriteRenderer> holes{};
  P<SpriteRenderer> rays{};
  // ---- constructors
  LocationAttic2Start() {}
  // ---- methods
  void Start();
  void Update();
  void forceTalk0();
  void forceTalk();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
