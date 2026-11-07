// Generated from Gasstation_Plates.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Gasstation_Plates.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Gasstation_Plates : public ObjectActionController {
public:
  // ---- constructors
  Gasstation_Plates() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void stopAnimation();
  void hiss();
  void play_animation();
  void run_like_hell();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
