// Generated from LocationOutpost4Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost4Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost4Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> light2{};
  P<SpriteRenderer> light3{};
  bool lights_bool{};
  int lights_int{};
  P<GameObject> npc1_target{};
  P<GameObject> npc2_target{};
  P<GameObject> npc3_target{};
  bool gingerShowFinger{};
  P<NPCWalkController> ginger{};
  // ---- constructors
  LocationOutpost4Start() {}
  // ---- methods
  void Start();
  void moveNpc2();
  void moveNpc3();
  void Update();
  void gingerGoAway(String val = S(""));
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
