// Generated from BarnButtonGenOff.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnButtonGenOff.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnButtonGenOff : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> engineStart{};
  P<AudioClip> engineDie{};
  P<AudioClip> engineRun{};
  P<AudioSource> aS{};
  // ---- constructors
  BarnButtonGenOff() {}
  // ---- methods
  void Start();
  void unlockIt();
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
