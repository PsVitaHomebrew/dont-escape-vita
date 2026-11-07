// Generated from LocationDesertFence2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDesertFence2Start.cpp
#pragma once
#include "../game_types.h"

class LocationDesertFence2Start : public MonoBehaviour {
public:
  // ---- fields
  P<Sprite> hammerDown{};
  // ---- constructors
  LocationDesertFence2Start() {}
  // ---- methods
  void Start();
  void makeItLast(String a);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
