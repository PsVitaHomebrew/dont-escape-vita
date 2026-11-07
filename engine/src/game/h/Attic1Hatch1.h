// Generated from Attic1Hatch1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Attic1Hatch1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Attic1Hatch1 : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> klapaFlag{};
  P<Sprite> klapaBlanket{};
  P<Sprite> klapaBlanketb{};
  P<Sprite> klapaThermb{};
  // ---- constructors
  Attic1Hatch1() {}
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
