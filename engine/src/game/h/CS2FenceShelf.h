// Generated from CS2FenceShelf.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS2FenceShelf.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS2FenceShelf : public ObjectActionController {
public:
  // ---- fields
  P<Animator> crow{};
  // ---- constructors
  CS2FenceShelf() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
