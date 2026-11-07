// Generated from LocationUpstairsHatchFall.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationUpstairsHatchFall.cpp
#pragma once
#include "../game_types.h"

class LocationUpstairsHatchFall : public MonoBehaviour {
public:
  // ---- constructors
  LocationUpstairsHatchFall() {}
  // ---- methods
  void Start();
  void Update();
  void endFall();
  void jebs();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
