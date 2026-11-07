// Generated from LocationEnding4.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationEnding4.cpp
#pragma once
#include "../game_types.h"

class LocationEnding4 : public MonoBehaviour {
public:
  // ---- constructors
  LocationEnding4() {}
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
