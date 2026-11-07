// Generated from OutpostOutsideRadar.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostOutsideRadar.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class OutpostOutsideRadar : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  bool wstan{};
  P<Sprite> open{};
  P<Sprite> closed{};
  P<GameObject> walkHere{};
  P<GameObject> walkHere2{};
  P<PolygonCollider2D> blok{};
  P<SpriteRenderer> blysk{};
  float alpha{};
  float alphaDir{};
  // ---- constructors
  OutpostOutsideRadar() {}
  // ---- methods
  void Update();
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
