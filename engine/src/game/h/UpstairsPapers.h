// Generated from UpstairsPapers.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/UpstairsPapers.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class UpstairsPapers : public ObjectActionController {
public:
  // ---- constructors
  UpstairsPapers() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void take1(String param = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
