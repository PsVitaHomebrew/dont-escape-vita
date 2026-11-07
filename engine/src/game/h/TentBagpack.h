// Generated from TentBagpack.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TentBagpack.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TentBagpack : public ObjectActionController {
public:
  // ---- constructors
  TentBagpack() {}
  // ---- methods
  void Start();
  void whatOnClick() override;
  void clickAction() override;
  void fixShadow();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
