// Generated from InventoryCapMeterController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryCapMeterController.cpp
#pragma once
#include "../game_types.h"

class InventoryCapMeterController : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> tfc{};
  P<InventoryController> ic{};
  static P<InventoryCapMeterController> cm;
  // ---- constructors
  InventoryCapMeterController() {}
  // ---- methods
  void Awake();
  void Start();
  void Update();
  void updateText();
  void OnMouseEnter();
  void OnMouseExit();
  void OnMouseDown();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
