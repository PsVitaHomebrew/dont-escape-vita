// Generated from PesttruckLocker2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/PesttruckLocker2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class PesttruckLocker2 : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  // ---- constructors
  PesttruckLocker2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void yesClicked();
  void updateState() override;
  void clickAction2() override;
  void whatOnClick0() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
