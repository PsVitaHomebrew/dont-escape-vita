// Generated from LocationOutpostShipCloset.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpostShipCloset.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationOutpostShipCloset : public ObjectActionController {
public:
  // ---- constructors
  LocationOutpostShipCloset() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void upd(String a = S(""));
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
