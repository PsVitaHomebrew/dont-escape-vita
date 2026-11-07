// Generated from Barn_Heystack.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Barn_Heystack.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Barn_Heystack : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  // ---- constructors
  Barn_Heystack() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick() override;
  void clickAction() override;
  void yesClicked();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
