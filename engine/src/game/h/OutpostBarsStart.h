// Generated from OutpostBarsStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostBarsStart.cpp
#pragma once
#include "../game_types.h"

class OutpostBarsStart : public MonoBehaviour {
public:
  // ---- constructors
  OutpostBarsStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
