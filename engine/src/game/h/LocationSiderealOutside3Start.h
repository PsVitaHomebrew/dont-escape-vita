// Generated from LocationSiderealOutside3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealOutside3Start.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealOutside3Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationSiderealOutside3Start() {}
  // ---- methods
  void Start();
  void uuuu(String a = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
