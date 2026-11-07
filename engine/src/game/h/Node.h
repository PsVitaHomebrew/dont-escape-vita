// Generated from Node.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Node.cpp
#pragma once
#include "../game_types.h"

class Node : public Obj {
public:
  // ---- fields
  P<Node> ParentNode{};
  P<GameObject> gameObject{};
  Vector2 _Location_k{}; // auto-property backing
  Vector2 _GameLocation_k{}; // auto-property backing
  bool _IsWalkable_k{}; // auto-property backing
  float _G_k{}; // auto-property backing
  float _H_k{}; // auto-property backing
  NodeState _State_k{}; // auto-property backing
  // ---- constructors
  Node();
  Node(Vector2 pos, Vector2 pos2, bool clear);
  // ---- properties
  Vector2 get_Location();
  void set_Location(Vector2 value);
  Vector2 get_GameLocation();
  void set_GameLocation(Vector2 value);
  bool get_IsWalkable();
  void set_IsWalkable(bool value);
  float get_G();
  void set_G(float value);
  float get_H();
  void set_H(float value);
  float get_F();
  NodeState get_State();
  void set_State(NodeState value);
  // ---- methods
  static float GetTraversalCost(Vector2 p1, Vector2 p2);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
