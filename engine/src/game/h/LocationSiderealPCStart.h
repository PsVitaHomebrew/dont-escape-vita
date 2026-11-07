// Generated from LocationSiderealPCStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealPCStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealPCStart : public MonoBehaviour {
public:
  // ---- fields
  bool failsafe{};
  // ---- constructors
  LocationSiderealPCStart() {}
  // ---- methods
  void Start();
  void resetMail();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
