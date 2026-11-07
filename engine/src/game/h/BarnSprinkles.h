// Generated from BarnSprinkles.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnSprinkles.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnSprinkles : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  P<GameObject> lights{};
  // ---- constructors
  BarnSprinkles() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick() override;
  void clickAction() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
