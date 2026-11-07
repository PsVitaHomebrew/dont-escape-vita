// Generated from LoctionAttic1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LoctionAttic1Start.cpp
#pragma once
#include "../game_types.h"

class LoctionAttic1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> destroyed{};
  P<SpriteRenderer> holes{};
  P<SpriteRenderer> rays{};
  // ---- constructors
  LoctionAttic1Start() {}
  // ---- methods
  void Start();
  void Update();
  void backgroundCheck();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
