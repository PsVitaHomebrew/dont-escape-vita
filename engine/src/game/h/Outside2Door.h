// Generated from Outside2Door.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Outside2Door.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Outside2Door : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> soundOpen{};
  P<AudioClip> soundClose{};
  // ---- constructors
  Outside2Door() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
