// Generated from SiderealPCMailSelector.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealPCMailSelector.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealPCMailSelector : public ObjectActionController {
public:
  // ---- fields
  int mailNumber{};
  P<Sprite> mailHighlight{};
  P<SpriteRenderer> MHR{};
  List<P<WorldCaption>> wcs{};
  P<WorldCaption> caption{};
  P<WorldCaption> email{};
  P<SiderealComputerSound> beeper{};
  // ---- constructors
  SiderealPCMailSelector() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
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
