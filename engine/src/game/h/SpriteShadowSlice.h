// Generated from SpriteShadowSlice.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SpriteShadowSlice.cpp
#pragma once
#include "../game_types.h"

class SpriteShadowSlice : public Obj {
public:
  // ---- fields
  P<GameObject> shadowHolder{};
  P<SpriteRenderer> shadow{};
  P<SpriteMask> mask{};
  // ---- constructors
  SpriteShadowSlice() {}
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
