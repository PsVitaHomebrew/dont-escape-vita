// Generated from Door2_Exit.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Door2_Exit.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Door2_Exit : public ObjectActionController {
public:
  // ---- constructors
  Door2_Exit() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void Update();
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
