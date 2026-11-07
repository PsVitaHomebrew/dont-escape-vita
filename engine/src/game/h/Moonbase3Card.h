// Generated from Moonbase3Card.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Moonbase3Card.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Moonbase3Card : public ObjectActionController {
public:
  // ---- constructors
  Moonbase3Card() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
