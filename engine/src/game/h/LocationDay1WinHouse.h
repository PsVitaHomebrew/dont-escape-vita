// Generated from LocationDay1WinHouse.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay1WinHouse.cpp
#pragma once
#include "../game_types.h"

class LocationDay1WinHouse : public MonoBehaviour {
public:
  // ---- fields
  Vector2 realPosition{};
  P<Animator> thisAnimator{};
  P<AudioSource> aS{};
  P<LocationDay1WinHeli> heli{};
  // ---- constructors
  LocationDay1WinHouse() {}
  // ---- methods
  void Start();
  void Update();
  void startAnim();
  void startPan();
  void afterPan();
  void afterCrash();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
