// Generated from LocationEnding3.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationEnding3.cpp
#pragma once
#include "../game_types.h"

class LocationEnding3 : public MonoBehaviour {
public:
  // ---- constructors
  LocationEnding3() {}
  // ---- methods
  void Start();
  void nextScene();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
