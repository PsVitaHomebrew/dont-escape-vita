// Generated from LocationMoon1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoon1Start.cpp
#pragma once
#include "../game_types.h"

class LocationMoon1Start : public MonoBehaviour {
public:
  // ---- fields
  float time{};
  P<AudioSource> audioSouruce{};
  P<AudioSource> rumbler{};
  // ---- constructors
  LocationMoon1Start() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
