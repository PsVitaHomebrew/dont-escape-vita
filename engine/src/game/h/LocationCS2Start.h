// Generated from LocationCS2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCS2Start.cpp
#pragma once
#include "../game_types.h"

class LocationCS2Start : public MonoBehaviour {
public:
  // ---- fields
  P<Animator> thug{};
  P<Animator> crow{};
  bool shootArea{};
  bool playerShot{};
  P<ObjectActionController> exitcs1{};
  P<ObjectActionController> exitcs3{};
  // ---- constructors
  LocationCS2Start() {}
  // ---- methods
  void Start();
  void shootOrNot();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
