// Generated from GasstationCorpse.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationCorpse.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class GasstationCorpse : public ObjectActionController {
public:
  // ---- constructors
  GasstationCorpse() {}
  // ---- methods
  void Start();
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
