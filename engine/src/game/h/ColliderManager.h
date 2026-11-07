// Generated from ColliderManager.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ColliderManager.cpp
#pragma once
#include "../game_types.h"

class ColliderManager : public Obj {
public:
  // ---- fields
  List<P<PolygonCollider2D>> colliders = List<P<PolygonCollider2D>>::New();
  P<GameObject> gameObject{};
  P<PolygonCollider2D> currentColider{};
  // ---- constructors
  ColliderManager() {}
  // ---- methods
  void setTarget(P<GameObject> target, bool addNew = true);
  void setCollider(int number);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
