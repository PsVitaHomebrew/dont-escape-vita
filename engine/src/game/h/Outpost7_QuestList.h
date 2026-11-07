// Generated from Outpost7_QuestList.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost7_QuestList.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost7_QuestList : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  P<Sprite> paintingDE{};
  // ---- constructors
  Outpost7_QuestList() {}
  // ---- methods
  void Start();
  List<String> quests();
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
