// Generated from Attic1Hatch1b.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Attic1Hatch1b.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Attic1Hatch1b : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> light1{};
  P<Sprite> light2{};
  // ---- constructors
  Attic1Hatch1b() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
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
