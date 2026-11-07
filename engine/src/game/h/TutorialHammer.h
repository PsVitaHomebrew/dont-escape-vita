// Generated from TutorialHammer.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TutorialHammer.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TutorialHammer : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  // ---- constructors
  TutorialHammer() {}
  // ---- methods
  void Start();
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
