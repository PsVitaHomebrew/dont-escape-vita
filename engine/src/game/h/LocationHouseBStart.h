// Generated from LocationHouseBStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationHouseBStart.cpp
#pragma once
#include "../game_types.h"

class LocationHouseBStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> snow{};
  P<SpriteRenderer> snow2{};
  // ---- constructors
  LocationHouseBStart() {}
  // ---- methods
  void Start();
  void zalosne();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
