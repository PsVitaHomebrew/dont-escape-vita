// Generated from LocationCaveACPlug.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCaveACPlug.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationCaveACPlug : public ObjectActionController {
public:
  // ---- fields
  P<CursorController> cursorController{};
  P<Sprite> cord1{};
  P<Sprite> cord2{};
  // ---- constructors
  LocationCaveACPlug() {}
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
