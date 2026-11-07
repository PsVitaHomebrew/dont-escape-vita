// Generated from BaseWindow.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseWindow.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BaseWindow : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> glass{};
  P<Sprite> bars{};
  P<Sprite> net{};
  P<Sprite> foil{};
  P<Sprite> blanket{};
  P<Sprite> blanketb{};
  P<Sprite> flag{};
  P<Sprite> therm{};
  P<Sprite> board{};
  // ---- constructors
  BaseWindow() {}
  // ---- methods
  void Start();
  void clickAction2() override;
  void clickAction() override;
  void updateState() override;
  void whatOnClick() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
