// Generated from LocationMoon2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoon2Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoon2Start : public MonoBehaviour {
public:
  // ---- fields
  float time{};
  P<PolygonCollider2D> pc2{};
  P<AudioSource> audioSouruce{};
  P<AudioSource> rumbler{};
  // ---- constructors
  LocationMoon2Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
