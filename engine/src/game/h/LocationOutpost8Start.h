// Generated from LocationOutpost8Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost8Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost8Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> sr1{};
  P<SpriteRenderer> sr2{};
  P<SpriteRenderer> sr3{};
  // ---- constructors
  LocationOutpost8Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
