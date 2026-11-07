// Generated from LocationEnding2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationEnding2.cpp
#pragma once
#include "../game_types.h"

class LocationEnding2 : public MonoBehaviour {
public:
  // ---- constructors
  LocationEnding2() {}
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
