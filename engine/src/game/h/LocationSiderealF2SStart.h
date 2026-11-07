// Generated from LocationSiderealF2SStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF2SStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF2SStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> dark{};
  P<SpriteRenderer> light{};
  P<SpriteRenderer> light2{};
  P<SpriteRenderer> shadows{};
  P<SpriteRenderer> pc_on{};
  P<SpriteRenderer> pc_off{};
  // ---- constructors
  LocationSiderealF2SStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
