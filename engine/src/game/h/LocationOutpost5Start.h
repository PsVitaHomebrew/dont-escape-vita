// Generated from LocationOutpost5Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost5Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpost5Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> light2{};
  P<SpriteRenderer> light3{};
  P<GameObject> playerTarget{};
  P<GameObject> npc1_target{};
  P<GameObject> npc2_target{};
  P<GameObject> npc3_target{};
  P<NPCWalkController> codyWalker{};
  bool codyRun{};
  bool firstTime{};
  int lights{};
  // ---- constructors
  LocationOutpost5Start() {}
  // ---- methods
  void Start();
  void forceTalk1();
  void walkthere();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
