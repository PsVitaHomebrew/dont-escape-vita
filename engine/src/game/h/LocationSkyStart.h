// Generated from LocationSkyStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSkyStart.cpp
#pragma once
#include "../game_types.h"

class LocationSkyStart : public MonoBehaviour {
public:
  // ---- fields
  P<GameObject> fakePlayer{};
  List<float> realY{};
  List<float> speed{};
  List<float> target{};
  List<P<GameObject>> layer{};
  float speedMod{};
  bool transition{};
  float realFakePlayerX{};
  float ambientVol = 1.0f;
  // ---- constructors
  LocationSkyStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
