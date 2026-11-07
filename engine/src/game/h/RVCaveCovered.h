// Generated from RVCaveCovered.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/RVCaveCovered.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class RVCaveCovered : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> light1{};
  P<Sprite> light2{};
  // ---- constructors
  RVCaveCovered() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void doRemove();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
