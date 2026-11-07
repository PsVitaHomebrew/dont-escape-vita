// Generated from BarnButtonX.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnButtonX.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnButtonX : public ObjectActionController {
public:
  // ---- fields
  P<AudioSource> aS{};
  P<AudioClip> engineRun{};
  // ---- constructors
  BarnButtonX() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateAfterAnimation();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
