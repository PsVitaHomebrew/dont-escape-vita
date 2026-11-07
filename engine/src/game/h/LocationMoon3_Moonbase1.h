// Generated from LocationMoon3_Moonbase1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoon3_Moonbase1.cpp
#pragma once
#include "../game_types.h"

class LocationMoon3_Moonbase1 : public MonoBehaviour {
public:
  // ---- constructors
  LocationMoon3_Moonbase1() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
