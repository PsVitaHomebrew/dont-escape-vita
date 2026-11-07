// Generated from LocationSiderealClimbStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealClimbStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealClimbStart : public MonoBehaviour {
public:
  // ---- fields
  P<GameObject> tlo1{};
  P<GameObject> tlo2{};
  P<GameObject> tlo3{};
  P<GameObject> tlo4{};
  P<SpriteRenderer> moong{};
  int shift = 55;
  P<NPCWalkController> npc1{};
  P<NPCWalkController> npc2{};
  P<NPCWalkController> npc3{};
  // ---- constructors
  LocationSiderealClimbStart() {}
  // ---- methods
  void Start();
  void suwsuw(P<NPCWalkController> npc, int dist);
  void Update();
  bool nawig(P<NPCWalkController> npc, P<GameObject> nav);
  void przesuw(P<GameObject> go, float skala, float bonbon);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
