// Generated from Restaurant5Danger.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Restaurant5Danger.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Restaurant5Danger : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> bugs_dead{};
  P<Sprite> webs_dead{};
  P<Sprite> webs{};
  P<GameObject> zmarker{};
  List<P<BugFly>> flies{};
  // ---- constructors
  Restaurant5Danger() {}
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
