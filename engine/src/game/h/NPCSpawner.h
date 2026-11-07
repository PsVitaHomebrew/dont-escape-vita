// Generated from NPCSpawner.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/NPCSpawner.cpp
#pragma once
#include "../game_types.h"

class NPCSpawner : public MonoBehaviour {
public:
  // ---- fields
  bool ifEntriesMatch{};
  float rand_del_min = 0.5f;
  float rand_del_max = 3.0f;
  bool flipX{};
  String npcName = String(u"");
  P<NPCWalkController> npc{};
  P<BoxCollider2D> collider{};
  float targetAlpha = 1.0f;
  float alpha = 1.0f;
  P<SpriteRenderer> spriteRenderer{};
  List<String> conditions{};
  List<bool> conditionsValues{};
  List<String> basicConditions{};
  String mainCondition{};
  bool spawn = true;
  String startAnimation = String(u"");
  P<LocationManager> currentLocationManager{};
  // ---- constructors
  NPCSpawner() {}
  // ---- methods
  void Start();
  void spawnOrNot(bool resumingGame = false);
  void flipage();
  void hide(bool fast = true);
  void show(bool fast = true);
  void arrive();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
