// Generated from ItemData.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ItemData.cpp
#pragma once
#include "../game_types.h"

class ItemData : public Obj {
public:
  // ---- fields
  String id{};
  int locX{};
  int locY{};
  String droppedLocation{};
  // ---- constructors
  ItemData();
  ItemData(String _id, String _droppedLocation, int _locX, int _locY);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
