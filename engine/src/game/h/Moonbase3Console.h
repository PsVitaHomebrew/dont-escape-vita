// Generated from Moonbase3Console.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Moonbase3Console.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Moonbase3Console : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> painting{};
  // ---- constructors
  Moonbase3Console() {}
  // ---- methods
  void Start();
  List<String> quests();
  void failsound(String s = S(""));
  void examine(String val = S(""));
  void say1();
  void say2();
  void clickAction() override;
  void ohNo();
  void opennocate();
  void updateState() override;
  void startDialogue2(String str_ = S(""));
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
