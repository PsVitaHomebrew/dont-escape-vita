// Generated from LocationDay1WinHeli.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay1WinHeli.cpp
#pragma once
#include "../game_types.h"

class LocationDay1WinHeli : public MonoBehaviour {
public:
  // ---- fields
  Vector2 realPosition{};
  P<LocationDay1WinHouse> house{};
  P<Animator> houseAnimator{};
  P<Animator> thisAnimator{};
  P<AudioSource> aS{};
  float targetX{};
  float targetY{};
  bool crashing{};
  int crashDel{};
  bool launched{};
  float speed{};
  // ---- constructors
  LocationDay1WinHeli() {}
  // ---- methods
  void Start();
  void Update();
  void crash();
  void crash2();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
