// Generated from ResultsChapterShipAir.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ResultsChapterShipAir.cpp
#pragma once
#include "../game_types.h"
#include "ResultsController.h"

class ResultsChapterShipAir : public ResultsController {
public:
  // ---- fields
  float time{};
  P<SpriteRenderer> sr{};
  P<SpriteRenderer> sr2{};
  P<Sprite> launch_sprite{};
  P<Sprite> fly_sprite_1{};
  P<Sprite> fly_sprite_2{};
  P<Sprite> fly_sprite_3{};
  P<Sprite> fly_sprite_4{};
  P<Sprite> launch_spriteF{};
  P<Sprite> fly_sprite_1F{};
  P<Sprite> fly_sprite_2F{};
  P<Sprite> fly_sprite_3F{};
  P<Sprite> fly_sprite_4F{};
  float show_launch{};
  bool show_flight{};
  String analytics_aux_tanks = S("false");
  String analytics_filters = S("false");
  String analytics_hull = S("false");
  String analytics_launched = S("false");
  String analytics_mixture = S("0");
  String analytics_pills = S("0");
  // ---- constructors
  ResultsChapterShipAir() {}
  // ---- methods
  void changeMusic(String s = S(""));
  void changeView(String s = S(""));
  void Update();
  void chapterResult() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
