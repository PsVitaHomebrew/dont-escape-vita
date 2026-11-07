// Generated from LocationHouseBBackStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationHouseBBackStart.cpp
#pragma once
#include "../game_types.h"

class LocationHouseBBackStart : public MonoBehaviour {
public:
  // ---- fields
  P<NPCWalkController> barry{};
  P<SpriteRenderer> snow{};
  // ---- constructors
  LocationHouseBBackStart() {}
  // ---- methods
  void Start();
  void codyJump0(String v = S(""));
  void codyJump(String v = S(""));
  void codyJump2(String v = S(""));
  void codyJump4(String v = S(""));
  void codyJump3(String v = S(""));
  void joinTeam(String val = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
