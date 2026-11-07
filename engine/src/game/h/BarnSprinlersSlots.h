// Generated from BarnSprinlersSlots.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnSprinlersSlots.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnSprinlersSlots : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  P<PolygonCollider2D> poly1{};
  P<PolygonCollider2D> poly2{};
  P<Sprite> barn_sprinkles_empty{};
  P<Sprite> barn_sprinkles_1{};
  P<Sprite> barn_sprinkles_2{};
  P<Sprite> barn_sprinkles_single_filled{};
  P<Sprite> barn_sprinkles_single_empty{};
  P<Sprite> barn_sprinkles_single_12{};
  P<Sprite> barn_sprinkles_single_23{};
  P<Sprite> barn_sprinkles_single_13{};
  P<Sprite> barn_sprinkles_single_mix_used{};
  // ---- constructors
  BarnSprinlersSlots() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick() override;
  void clickAction() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
