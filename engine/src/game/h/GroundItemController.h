// Generated from GroundItemController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GroundItemController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GroundItemController : public ObjectActionController {
public:
  // ---- fields
  P<Item> itemRef{};
  P<SpriteRenderer> spriteRenderer{};
  int delay{};
  int frame{};
  P<SpriteRenderer> frontView{};
  static int xOffset;
  static int yOffset;
  bool canPickUp = true;
  P<GameObject> inventory{};
  // ---- constructors
  GroundItemController() {}
  // ---- methods
  void Awake();
  void init(P<Item> item);
  void Update();
  void Start();
  void disablePickup();
  void enablePickup();
  void whatOnClick() override;
  void clickAction() override;
  void clickAction2() override;
  void updateState() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
