// Generated from LocationRVInspect.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRVInspect.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationRVInspect : public ObjectActionController {
public:
  // ---- fields
  P<AudioSource> aS{};
  P<ParticleGenerator> smoke{};
  // ---- constructors
  LocationRVInspect() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
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
