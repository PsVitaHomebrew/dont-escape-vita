// Generated from Cave_Socket_Placed.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Cave_Socket_Placed.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Cave_Socket_Placed : public ObjectActionController {
public:
  // ---- fields
  P<CursorController> cursorController{};
  String test{};
  // ---- constructors
  Cave_Socket_Placed() {}
  // ---- properties
  String get_Test();
  void set_Test(String value);
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void takeCord(String param = S(""));
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
