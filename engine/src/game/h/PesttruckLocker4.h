// Generated from PesttruckLocker4.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/PesttruckLocker4.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class PesttruckLocker4 : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  // ---- constructors
  PesttruckLocker4() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
