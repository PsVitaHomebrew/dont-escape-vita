// Generated from MixerResults.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MixerResults.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class MixerResults : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> sprite_1{};
  P<Sprite> sprite_2{};
  P<Sprite> sprite_3{};
  int liczba{};
  String thisNumber{};
  // ---- constructors
  MixerResults() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void resetMixer(String param = S(""));
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
