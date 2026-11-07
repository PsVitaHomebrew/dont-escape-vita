// Generated from CursorController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CursorController.cpp
#pragma once
#include "../game_types.h"

class CursorController : public MonoBehaviour {
public:
  using PixelCursor = CursorController_PixelCursor;
  // ---- fields
  static P<CursorController> cc;
  P<SpriteRenderer> spriteRenderer{};
  CursorController_PixelCursor currentState{};
  CursorController_PixelCursor overrideState{};
  int decay{};
  P<GameObject> selectedItem{};
  String selectedItemName{};
  P<Item> selectedItemRef{};
  WalkController_Direction trans_dir = WalkController_Direction::S_;
  // ---- constructors
  CursorController() {}
  // ---- methods
  void Awake();
  void Start();
  void Update();
  void selectItem(P<Item> it);
  void deselectItem();
  void showCursor(CursorController_PixelCursor a, WalkController_Direction newDir = WalkController_Direction::S_);
  CursorController_PixelCursor getCurrentState();
  void clearOverride();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
