// Generated from BarnStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnStart.cpp
#pragma once
#include "../game_types.h"

class BarnStart : public MonoBehaviour {
public:
  // ---- constructors
  BarnStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
