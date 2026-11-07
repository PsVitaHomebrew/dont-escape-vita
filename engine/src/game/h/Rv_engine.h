// Generated from Rv_engine.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Rv_engine.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Rv_engine : public ObjectActionController {
public:
  // ---- fields
  P<AudioSource> aS{};
  // ---- constructors
  Rv_engine() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void examineCar(String str_);
  void doExamineCar();
  void sayAboutCarExplore2();
  void sayAboutCarExplore();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
