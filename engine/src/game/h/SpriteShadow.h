// Generated from SpriteShadow.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SpriteShadow.cpp
#pragma once
#include "../game_types.h"

class SpriteShadow : public Obj {
public:
  // ---- fields
  Array<P<SpriteShadowSlice>> shadows{};
  P<GameObject> gameObject{};
  P<Sprite> shadow_mask{};
  int offsetY{};
  int offsetY2{};
  float startAlpha = 1.0f;
  float alphaMod = 1.0f;
  float fadeRateH = 0.025f;
  float fadeRateV = 0.025f;
  float source = 160.0f;
  float scaleFactor = 0.75f;
  float skewFactor = 40.0f;
  float skewFactor2{};
  bool downwards = true;
  String lastFrame{};
  String lastScene{};
  int shadowOffsetY{};
  // ---- constructors
  SpriteShadow();
  SpriteShadow(P<GameObject> t);
  // ---- methods
  void clearLastFrame();
  void newShadowPiece(int i);
  void update(Vector3 postion, Vector2 currentXY, int offset);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
