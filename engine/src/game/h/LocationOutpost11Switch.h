// Generated from LocationOutpost11Switch.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost11Switch.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationOutpost11Switch : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> sprite_on{};
  P<Sprite> sprite_off{};
  P<Sprite> sprite_wr{};
  int liczba{};
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> light2{};
  String thisNumber{};
  bool projectorCutscene{};
  P<PolygonCollider2D> darkness{};
  // ---- constructors
  LocationOutpost11Switch() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void rotate2(String var = S(""));
  void gingerwalk(String var = S(""));
  void rotateLeft(String v = S(""));
  void rotateRight(String v = S(""));
  void rotate1();
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
