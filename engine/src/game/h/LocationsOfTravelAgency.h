// Generated from LocationsOfTravelAgency.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationsOfTravelAgency.cpp
#pragma once
#include "../game_types.h"

class LocationsOfTravelAgency : public Obj {
public:
  // ---- fields
  List<String> locations{};
  P<TravelAgency> travelAgency{};
  // ---- constructors
  LocationsOfTravelAgency() {}
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
