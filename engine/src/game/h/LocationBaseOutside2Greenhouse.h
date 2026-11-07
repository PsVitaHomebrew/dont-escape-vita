// Generated from LocationBaseOutside2Greenhouse.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseOutside2Greenhouse.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationBaseOutside2Greenhouse : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sprite1{};
  P<Sprite> sprite2{};
  P<Sprite> sprite3{};
  P<Sprite> sprite4{};
  P<Sprite> sprite5{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  LocationBaseOutside2Greenhouse() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick() override;
  void clickAction() override;
  void yesClicked2();
  void yesClicked();
  void nailsremove(String s);
  void drop();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
