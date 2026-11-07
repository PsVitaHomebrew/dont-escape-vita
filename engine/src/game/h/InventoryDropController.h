// Generated from InventoryDropController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryDropController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class InventoryDropController : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> inventoryButton{};
  P<CursorController> cursorController{};
  P<InventoryController> invetoryController{};
  P<ItemsManager> itemsManager{};
  P<WalkController> walkControllerr{};
  // ---- constructors
  InventoryDropController() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void OnMouseEnter();
  void OnMouseExit();
  void OnMouseDown();
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
