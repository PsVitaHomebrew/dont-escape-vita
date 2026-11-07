// Generated from Outpost8Injector.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outpost8Injector.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outpost8Injector : public ObjectActionController {
public:
  // ---- constructors
  Outpost8Injector() {}
  // ---- methods
  void Start();
  void beep();
  void bzzt();
  void clickAction() override;
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
