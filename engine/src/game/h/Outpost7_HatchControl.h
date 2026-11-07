// Generated from Outpost7_HatchControl.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost7_HatchControl.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost7_HatchControl : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> background{};
  P<Animator> animator{};
  P<ParticleGenerator> pg1{};
  P<ParticleGenerator> pg2{};
  P<ParticleGenerator> pg3{};
  // ---- constructors
  Outpost7_HatchControl() {}
  // ---- methods
  void Start();
  void yesOpen();
  void succeed();
  void stopSand();
  void failed();
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
