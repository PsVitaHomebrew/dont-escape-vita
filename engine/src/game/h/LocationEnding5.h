// Generated from LocationEnding5.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationEnding5.cpp
#pragma once
#include "../game_types.h"

class LocationEnding5 : public MonoBehaviour {
public:
  // ---- constructors
  LocationEnding5() {}
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
