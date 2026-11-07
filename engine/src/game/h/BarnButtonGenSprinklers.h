// Generated from BarnButtonGenSprinklers.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnButtonGenSprinklers.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnButtonGenSprinklers : public ObjectActionController {
public:
  // ---- fields
  P<BarnButtonGenOff> bbgo{};
  // ---- constructors
  BarnButtonGenSprinklers() {}
  // ---- methods
  void Start();
  void unlockIt();
  void clickAction() override;
  void updateAfterAnimation();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
