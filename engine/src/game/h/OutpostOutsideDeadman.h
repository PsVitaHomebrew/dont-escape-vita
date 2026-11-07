// Generated from OutpostOutsideDeadman.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostOutsideDeadman.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class OutpostOutsideDeadman : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> crack{};
  P<Sprite> spaw{};
  // ---- constructors
  OutpostOutsideDeadman() {}
  // ---- methods
  void Start();
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
