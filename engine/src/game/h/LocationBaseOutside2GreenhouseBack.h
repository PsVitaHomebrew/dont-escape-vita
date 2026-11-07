// Generated from LocationBaseOutside2GreenhouseBack.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseOutside2GreenhouseBack.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationBaseOutside2GreenhouseBack : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  P<Sprite> sprite3{};
  P<Sprite> sprite4{};
  P<Sprite> sprite5{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  LocationBaseOutside2GreenhouseBack() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick() override;
  void clickAction() override;
  void restore();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
