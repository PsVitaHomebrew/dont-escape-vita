// Generated from LocationSiderealRoofStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealRoofStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealRoofStart : public MonoBehaviour {
public:
  // ---- fields
  P<LetterFall> lf{};
  // ---- constructors
  LocationSiderealRoofStart() {}
  // ---- methods
  void Start();
  void setWalkablePath();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
