// Generated from InventoryButtonController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryButtonController.cpp
#pragma once
#include "../game_types.h"

class InventoryButtonController : public MonoBehaviour {
public:
  // ---- fields
  String frame_name{};
  String frame_name_sufix{};
  bool isOpen{};
  P<InventoryController> inventory{};
  P<InventoryCapMeterController> invCapCont{};
  Vector2 pozycja{};
  static P<InventoryButtonController> ibc;
  bool spaceWasPressed{};
  bool justClosed{};
  // ---- constructors
  InventoryButtonController() {}
  // ---- methods
  void Awake();
  bool isItOpen();
  void Start();
  void Update();
  void open(int invno = 0);
  void unstuckTrunk();
  void close();
  void showInventory(String param);
  void showFinal();
  void show();
  void hide();
  void openTrunk();
  void openChest();
  void OnMouseOver();
  void OnMouseExit();
  void fakeMouseClick(bool spacja = false);
  void OnMouseDown();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
