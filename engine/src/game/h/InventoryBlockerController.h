// Generated from InventoryBlockerController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/InventoryBlockerController.cpp
#pragma once
#include "../game_types.h"

class InventoryBlockerController : public MonoBehaviour {
public:
  // ---- constructors
  InventoryBlockerController() {}
  // ---- methods
  void Start();
  void Update();
  void OnMouseEnter();
  void OnMouseDown();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
