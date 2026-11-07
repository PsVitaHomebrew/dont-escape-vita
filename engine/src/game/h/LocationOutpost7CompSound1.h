// Generated from LocationOutpost7CompSound1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost7CompSound1.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost7CompSound1 : public MonoBehaviour {
public:
  // ---- fields
  List<P<AudioClip>> dzwieki{};
  P<AudioSource> aS{};
  // ---- constructors
  LocationOutpost7CompSound1() {}
  // ---- methods
  void Start();
  void Update();
  void makeDatSound();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
