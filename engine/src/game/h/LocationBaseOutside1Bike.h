// Generated from LocationBaseOutside1Bike.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseOutside1Bike.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationBaseOutside1Bike : public ObjectActionController {
public:
  // ---- fields
  float alpha{};
  float dir{};
  bool stopped{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  LocationBaseOutside1Bike() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void standup(String s = S(""));
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
