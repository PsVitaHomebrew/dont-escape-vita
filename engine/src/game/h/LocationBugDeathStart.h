// Generated from LocationBugDeathStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBugDeathStart.cpp
#pragma once
#include "../game_types.h"

class LocationBugDeathStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationBugDeathStart() {}
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
