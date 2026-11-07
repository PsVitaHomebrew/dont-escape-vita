// Generated from Restaurant2Trash.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant2Trash.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant2Trash : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> trashCollider{};
  // ---- constructors
  Restaurant2Trash() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void pushLittleCart_Barry();
  void pushLittleCart_Cate();
  void pushLittleCart();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
