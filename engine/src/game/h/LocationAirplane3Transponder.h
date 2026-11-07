// Generated from LocationAirplane3Transponder.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationAirplane3Transponder.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationAirplane3Transponder : public ObjectActionController {
public:
  // ---- fields
  float alpha{};
  float dir{};
  bool stopped{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  LocationAirplane3Transponder() {}
  // ---- methods
  void Start();
  void Update();
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
