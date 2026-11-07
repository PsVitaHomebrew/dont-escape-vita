// Generated from BarnGeneratorPull.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnGeneratorPull.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnGeneratorPull : public ObjectActionController {
public:
  // ---- fields
  P<BarnButtonGenOff> bbgo{};
  // ---- constructors
  BarnGeneratorPull() {}
  // ---- methods
  void Start();
  void unlockIt();
  void no_pull_pull();
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
