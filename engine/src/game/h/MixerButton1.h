// Generated from MixerButton1.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MixerButton1.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class MixerButton1 : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> sprite_on{};
  P<Sprite> sprite_off{};
  P<Sprite> sprite_wr{};
  int liczba{};
  String thisNumber{};
  // ---- constructors
  MixerButton1() {}
  // ---- methods
  void Start();
  void Update();
  void whatOnClick() override;
  void clickAction() override;
  void countThem();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
