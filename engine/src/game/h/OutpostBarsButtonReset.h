// Generated from OutpostBarsButtonReset.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostBarsButtonReset.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class OutpostBarsButtonReset : public ObjectActionController {
public:
  // ---- fields
  P<OutpostBarsButtonAdd> button_a{};
  P<OutpostBarsButtonAdd> button_b{};
  P<OutpostBarsButtonAdd> button_c{};
  P<OutpostBarsButtonAdd> button_d{};
  P<OutpostBarsButtonAdd> button_e{};
  P<Sprite> sprite_on{};
  P<Sprite> sprite_off{};
  P<Sprite> sprite_disabled{};
  P<SpriteRenderer> sr{};
  P<TextFieldController> label{};
  P<AudioSource> aS{};
  bool allowed{};
  // ---- constructors
  OutpostBarsButtonReset() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void zrobCos(P<OutpostBarsButtonAdd> obiekt, String nazwa, int minus);
  void unlock();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
