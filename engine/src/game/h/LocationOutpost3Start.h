// Generated from LocationOutpost3Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost3Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost3Start : public MonoBehaviour {
public:
  // ---- constructors
  LocationOutpost3Start() {}
  // ---- methods
  void setEntered(String s = S(""));
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
