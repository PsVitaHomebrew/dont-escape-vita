// Generated from LocationOutpost6Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost6Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost6Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> grate{};
  // ---- constructors
  LocationOutpost6Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
