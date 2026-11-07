// Generated from LocationKitchenKey.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationKitchenKey.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationKitchenKey : public ObjectActionController {
public:
  // ---- fields
  bool shined{};
  // ---- constructors
  LocationKitchenKey() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void shine();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
