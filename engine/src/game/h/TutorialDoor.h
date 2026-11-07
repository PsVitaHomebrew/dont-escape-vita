// Generated from TutorialDoor.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TutorialDoor.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TutorialDoor : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  // ---- constructors
  TutorialDoor() {}
  // ---- methods
  void Start();
  void creak1();
  void creak2();
  void creak3();
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
