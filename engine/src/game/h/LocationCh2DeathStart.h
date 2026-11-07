// Generated from LocationCh2DeathStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCh2DeathStart.cpp
#pragma once
#include "../game_types.h"

class LocationCh2DeathStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationCh2DeathStart() {}
  // ---- methods
  void Start();
  void end(String param);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
