// Generated from InventoryController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryController.cpp
#pragma once
#include "../game_types.h"

class InventoryController : public MonoBehaviour {
public:
  // ---- fields
  P<GameObject> inventoryButton{};
  P<TextFieldController> inventoryCloseButtonTextfield{};
  P<TextFieldController> inventoryCloseButtonTextfield2{};
  Array<P<InventoryItemController>> invItems{};
  Array<P<InventoryItemController>> trunkItems{};
  Array<P<InventoryItemController>> chestItems{};
  P<GameObject> trunk{};
  P<GameObject> chest{};
  static P<InventoryController> ic;
  P<AudioSource> aS{};
  P<InventoryCapMeterController> capMeter{};
  P<PolygonCollider2D> blocker{};
  int maxCapacity = 30;
  P<Button> InvTrunkClose{};
  P<Button> InvChestClose{};
  // ---- constructors
  InventoryController() {}
  // ---- methods
  void Awake();
  void Start();
  void cleanUp();
  void CloseTrunkButtonClicked();
  void CloseChestButtonClicked();
  void Update();
  void OnMouseEnter();
  void OnMouseExit();
  void loadItem(P<Item> item);
  void loadChestItem(P<Item> item);
  void loadTrunkItem(P<Item> item);
  P<InventoryItemController> findFreeSpot();
  P<InventoryItemController> findFreeSpotInTrunk();
  P<InventoryItemController> findFreeSpotInChest();
  bool putItemInTrunk(String itemName, bool quiet = false);
  bool putItemInChest(String itemName, bool quiet = false);
  float getCurrentWeight();
  void removeItem(String name);
  void clearInventory();
  static String getRoundedWeightLeft();
  bool pickUpItem(P<Item> itemRef, bool silent = false);
  void dropItem(P<Item> itemRef, bool remov = false, bool bow = false);
  bool pickOrDropItem(P<Item> itemRef, bool silent = false);
  bool isItemEquipped(String item);
  bool isUnequipped(String item);
  bool isItemInInventory(String item);
  bool isItemInInventoryOrTrunkOrWhatever(String item);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
