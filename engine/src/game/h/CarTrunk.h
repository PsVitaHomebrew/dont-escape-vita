// Generated from CarTrunk.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CarTrunk.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CarTrunk : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> sign{};
  float timeToOpenAgain{};
  P<GameObject> actionMarker1{};
  P<GameObject> actionMarker2{};
  // ---- constructors
  CarTrunk() {}
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
