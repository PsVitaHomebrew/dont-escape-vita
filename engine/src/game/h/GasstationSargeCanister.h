// Generated from GasstationSargeCanister.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationSargeCanister.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationSargeCanister : public ObjectActionController {
public:
  // ---- constructors
  GasstationSargeCanister() {}
  // ---- methods
  void Start();
  void whatOnClick() override;
  void clickAction() override;
  void updateState() override;
  void clickAction0() override;
  void clickAction2() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
