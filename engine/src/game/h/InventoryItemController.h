// Generated from InventoryItemController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryItemController.cpp
#pragma once
#include "../game_types.h"

class InventoryItemController : public MonoBehaviour {
public:
  // ---- fields
  P<GameObject> itemIcon{};
  float weight{};
  String itemName = String(u"");
  P<GameObject> cursor{};
  P<CursorController> cursorController{};
  P<SpriteRenderer> spriteRenderer{};
  P<SpriteRenderer> iconSpriteRenderer{};
  P<TextFieldController> textfield{};
  P<WalkController> walkController{};
  P<PlayerController> playerController{};
  P<InventoryController> invetoryController{};
  int lx{};
  int ly{};
  int shiftX{};
  int shiftY{};
  P<ItemsManager> itemsManager{};
  P<Item> itemRef{};
  float hover{};
  float displayHover{};
  // ---- constructors
  InventoryItemController() {}
  // ---- methods
  void Start();
  void Awake();
  void Update();
  void OnEnable();
  void OnMouseEnter();
  void OnMouseExit();
  void loadItem(P<Item> item);
  void removeItem();
  void OnMouseDown();
  void examineItem();
  void OnMouseOver();
  String getName();
  float getWeight();
  void znik();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
