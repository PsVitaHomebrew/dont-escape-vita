// Generated from HuntersLodgeOutside1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeOutside1Start.cpp
#pragma once
#include "../game_types.h"

class HuntersLodgeOutside1Start : public MonoBehaviour {
public:
  // ---- constructors
  HuntersLodgeOutside1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
