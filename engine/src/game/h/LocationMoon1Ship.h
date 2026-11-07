// Generated from LocationMoon1Ship.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoon1Ship.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationMoon1Ship : public ObjectActionController {
public:
  // ---- constructors
  LocationMoon1Ship() {}
  // ---- methods
  void Start();
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
