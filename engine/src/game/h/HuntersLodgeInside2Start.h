// Generated from HuntersLodgeInside2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeInside2Start.cpp
#pragma once
#include "../game_types.h"

class HuntersLodgeInside2Start : public MonoBehaviour {
public:
  // ---- constructors
  HuntersLodgeInside2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
