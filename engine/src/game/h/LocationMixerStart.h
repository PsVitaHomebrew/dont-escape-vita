// Generated from LocationMixerStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMixerStart.cpp
#pragma once
#include "../game_types.h"

class LocationMixerStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationMixerStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
