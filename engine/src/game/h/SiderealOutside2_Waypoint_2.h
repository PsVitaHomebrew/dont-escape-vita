// Generated from SiderealOutside2_Waypoint_2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealOutside2_Waypoint_2.cpp
#pragma once
#include "../game_types.h"

class SiderealOutside2_Waypoint_2 : public MonoBehaviour {
public:
  // ---- constructors
  SiderealOutside2_Waypoint_2() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
