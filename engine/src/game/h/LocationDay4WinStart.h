// Generated from LocationDay4WinStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay4WinStart.cpp
#pragma once
#include "../game_types.h"

class LocationDay4WinStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationDay4WinStart() {}
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
