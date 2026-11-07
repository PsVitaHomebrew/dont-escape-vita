// Generated from HuntersLodgeTreeStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HuntersLodgeTreeStart.cpp
#pragma once
#include "../game_types.h"

class HuntersLodgeTreeStart : public MonoBehaviour {
public:
  // ---- constructors
  HuntersLodgeTreeStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
