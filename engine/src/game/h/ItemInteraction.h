// Generated from ItemInteraction.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ItemInteraction.cpp
#pragma once
#include "../game_types.h"

class ItemInteraction : public Obj {
public:
  // ---- fields
  String name = String(u"");
  String failText = String(u"");
  String animation = String(u"");
  std::function<void()> action{};
  int range{};
  // ---- constructors
  ItemInteraction();
  ItemInteraction(String n, String fail = S(""), std::function<void()> act = nullptr, String anim = S(""), int rang = 0);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
