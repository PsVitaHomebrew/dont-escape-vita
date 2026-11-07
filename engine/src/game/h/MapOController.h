// Generated from MapOController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MapOController.cpp
#pragma once
#include "../game_types.h"

class MapOController : public MonoBehaviour {
public:
  // ---- fields
  P<TravelAgency> currentTravelAgency{};
  Array<P<TravelAgency>> travelAgencies{};
  P<MapXController> xMark{};
  // ---- constructors
  MapOController() {}
  // ---- methods
  void Start();
  void Update();
  P<TravelAgency> getCurrentTravelAgency();
  void clearRoutes();
  void updateLocation(P<TravelAgency> target);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
