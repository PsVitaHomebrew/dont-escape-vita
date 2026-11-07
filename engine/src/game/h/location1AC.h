// Generated from location1AC.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/location1AC.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class location1AC : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> acSound{};
  P<Sprite> powered_ac{};
  P<Sprite> unpowered_ac{};
  P<CursorController> cursorController{};
  // ---- constructors
  location1AC() {}
  // ---- methods
  void Start();
  void Update();
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
