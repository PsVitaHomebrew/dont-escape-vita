// Generated from LocationDesertTitleStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDesertTitleStart.cpp
#pragma once
#include "../game_types.h"

class LocationDesertTitleStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationDesertTitleStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
