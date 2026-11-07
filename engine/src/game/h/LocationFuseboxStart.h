// Generated from LocationFuseboxStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationFuseboxStart.cpp
#pragma once
#include "../game_types.h"

class LocationFuseboxStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationFuseboxStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
