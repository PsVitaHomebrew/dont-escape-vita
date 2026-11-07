// Generated from SiderealF2SCBody.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealF2SCBody.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealF2SCBody : public ObjectActionController {
public:
  // ---- constructors
  SiderealF2SCBody() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void pickItUp(String param);
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
