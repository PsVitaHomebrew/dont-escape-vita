// Generated from LocationDay1WinStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay1WinStart.cpp
#pragma once
#include "../game_types.h"

class LocationDay1WinStart : public MonoBehaviour {
public:
  // ---- fields
  P<LocationDay1WinHouse> house{};
  // ---- constructors
  LocationDay1WinStart() {}
  // ---- methods
  void Start();
  void continueGame(String param);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
