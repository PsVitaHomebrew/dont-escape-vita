// Generated from HunterLodgeTree.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/HunterLodgeTree.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class HunterLodgeTree : public ObjectActionController {
public:
  // ---- fields
  P<PolygonCollider2D> blocker{};
  // ---- constructors
  HunterLodgeTree() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void climbTree();
  void climbTree3();
  void climbTree2();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
