// Generated from OutpostBarsButtonAdd.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostBarsButtonAdd.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class OutpostBarsButtonAdd : public ObjectActionController {
public:
  // ---- fields
  String plus_1{};
  String minus_1{};
  String minus_2{};
  String minus_3{};
  String minus_4{};
  P<OutpostBarsButtonAdd> minus1Obj{};
  P<OutpostBarsButtonAdd> minus2Obj{};
  P<OutpostBarsButtonAdd> minus3Obj{};
  P<OutpostBarsButtonAdd> minus4Obj{};
  P<Sprite> sprite_on{};
  P<Sprite> sprite_off{};
  P<Sprite> sprite_disabled{};
  P<GameObject> bar{};
  P<Sprite> bar_red{};
  P<Sprite> bar_yellow{};
  P<Sprite> bar_green{};
  P<SpriteRenderer> sr{};
  int xShift{};
  int yShift{};
  int targetValue{};
  int currentValue{};
  float delay{};
  int bigPlus = 8;
  int smallPlus{};
  int bigMinus = 2;
  int smallMinus = 2;
  int good_start{};
  int good_end{};
  int perfect_start{};
  int perfect_end{};
  P<AudioSource> aS{};
  bool allowed{};
  P<OutpostBarsPuzzleCaption_Eff> caption_eff{};
  // ---- constructors
  OutpostBarsButtonAdd() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void zrobCos(P<OutpostBarsButtonAdd> obiekt, String nazwa, int minus);
  void unlock();
  void updateState() override;
  Vector3 coords(Vector2 source);
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
