// Generated from CraneController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CraneController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CraneController : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> contrBack{};
  P<CraneLeverController> lever1{};
  P<CraneLeverController> lever2{};
  P<CraneLeverController> lever3{};
  // ---- constructors
  CraneController() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
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
