// Generated from LocationMoonbase1_2.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonbase1_2.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationMoonbase1_2 : public ObjectActionController {
public:
  // ---- constructors
  LocationMoonbase1_2() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void zamyk();
  void unlock();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
