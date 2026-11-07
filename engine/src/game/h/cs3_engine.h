// Generated from cs3_engine.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/cs3_engine.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class cs3_engine : public ObjectActionController {
public:
  // ---- constructors
  cs3_engine() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void updateState() override;
  void startSoundANdSmoke();
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
