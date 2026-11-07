// Generated from Objective.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Objective.cpp
#pragma once
#include "../game_types.h"

class Objective : public Obj {
public:
  // ---- fields
  String id{};
  bool state{};
  int detail{};
  // ---- constructors
  Objective();
  Objective(String _id, bool _state, int _detail = 0);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
