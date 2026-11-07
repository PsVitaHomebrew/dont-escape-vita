// Generated from SiderealPCInternet.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealPCInternet.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealPCInternet : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> spriter{};
  P<SiderealComputerSound> beeper{};
  P<Sprite> icon{};
  P<Sprite> window{};
  P<WorldCaption> caption{};
  P<WorldCaption> txt{};
  P<WorldCaption> iconCaption{};
  // ---- constructors
  SiderealPCInternet() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void makeItSo2();
  void makeItSo();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
