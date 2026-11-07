// Generated from AreaEffect.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/AreaEffect.cpp
#pragma once
#include "../game_types.h"

class AreaEffect : public MonoBehaviour {
public:
  // ---- fields
  P<ColliderManager> colliderManager{};
  LayerMask actionLayer{};
  Array<P<NPCWalkController>> npcs{};
  Array<Vector2> lastPos{};
  Vector2 playerPos{};
  // ---- constructors
  AreaEffect() {}
  // ---- methods
  void Awake();
  void Start();
  void refresh();
  void Update();
  virtual void Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) = 0;
  virtual void Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic) = 0;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
