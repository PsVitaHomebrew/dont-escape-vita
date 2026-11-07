// Generated from LocationSiderealF3CCollapse.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF3CCollapse.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationSiderealF3CCollapse : public ObjectActionController {
public:
  // ---- constructors
  LocationSiderealF3CCollapse() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
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
