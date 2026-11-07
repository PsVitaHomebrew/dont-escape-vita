// Generated from KitchenDoor.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/KitchenDoor.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class KitchenDoor : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  P<SpriteRenderer> darkness{};
  P<SpriteRenderer> darkness2{};
  P<SpriteRenderer> lightt{};
  P<SpriteRenderer> rainbow{};
  P<Sprite> rainbow_0{};
  P<Sprite> rainbow_1{};
  P<Sprite> rainbow_2{};
  P<Sprite> rainbow_3{};
  P<Sprite> rainbow_4{};
  P<KitchenAreaEffect> kae{};
  // ---- constructors
  KitchenDoor() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void whatOnClick() override;
  void clickAction2() override;
  void clickAction0() override;
  void shadowy(float shadowAmount);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
