// Generated from SpiderInsideController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SpiderInsideController.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SpiderInsideController : public ObjectActionController {
public:
  // ---- fields
  float realX = -0.825f;
  // ---- constructors
  SpiderInsideController() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
