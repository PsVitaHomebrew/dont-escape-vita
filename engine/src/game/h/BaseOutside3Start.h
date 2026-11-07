// Generated from BaseOutside3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseOutside3Start.cpp
#pragma once
#include "../game_types.h"

class BaseOutside3Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> snow{};
  P<SpriteRenderer> snowman{};
  // ---- constructors
  BaseOutside3Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
