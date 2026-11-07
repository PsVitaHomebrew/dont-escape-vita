// Generated from MapXController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MapXController.cpp
#pragma once
#include "../game_types.h"

class MapXController : public MonoBehaviour {
public:
  // ---- fields
  P<Sprite> target{};
  P<Sprite> targetCar{};
  P<TravelAgency> targetTravelAgency{};
  // ---- constructors
  MapXController() {}
  // ---- methods
  void Start();
  void Update();
  void hide();
  void updateLocation(P<TravelAgency> target);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
