// Generated from TutorialHandle.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TutorialHandle.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TutorialHandle : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  P<PolygonCollider2D> blocker{};
  // ---- constructors
  TutorialHandle() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void pullit();
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
