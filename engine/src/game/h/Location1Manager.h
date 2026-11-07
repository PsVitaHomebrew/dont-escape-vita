// Generated from Location1Manager.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Location1Manager.cpp
#pragma once
#include "../game_types.h"
#include "LocationManager.h"

class Location1Manager : public LocationManager {
public:
  // ---- constructors
  Location1Manager() {}
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
