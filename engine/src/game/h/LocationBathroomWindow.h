// Generated from LocationBathroomWindow.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBathroomWindow.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationBathroomWindow : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> foil{};
  P<Sprite> bars{};
  P<Sprite> net{};
  P<Sprite> foil_nailed{};
  P<Sprite> bars_nailed{};
  P<Sprite> net_nailed{};
  P<Sprite> foil_taped{};
  P<Sprite> bars_taped{};
  P<Sprite> net_taped{};
  P<Sprite> foil_taped_nailed{};
  P<Sprite> bars_taped_nailed{};
  P<Sprite> net_taped_nailed{};
  P<Sprite> foil_nailed_broken{};
  P<Sprite> bars_nailed_broken{};
  P<Sprite> net_nailed_broken{};
  P<Sprite> foil_taped_broken{};
  P<Sprite> bars_taped_broken{};
  P<Sprite> net_taped_broken{};
  P<Sprite> foil_taped_nailed_broken{};
  P<Sprite> bars_taped_nailed_broken{};
  P<Sprite> net_taped_nailed_broken{};
  P<Sprite> blanket{};
  P<Sprite> blanket_taped{};
  P<Sprite> blanket_nailed{};
  P<Sprite> blanket_taped_nailed{};
  P<Sprite> blanketb{};
  P<Sprite> blanketb_taped{};
  P<Sprite> blanketb_nailed{};
  P<Sprite> blanketb_taped_nailed{};
  P<Sprite> flag{};
  P<Sprite> flag_taped{};
  P<Sprite> flag_nailed{};
  P<Sprite> flag_taped_nailed{};
  P<Sprite> thermalb{};
  P<Sprite> thermalb_taped{};
  P<Sprite> thermalb_nailed{};
  P<Sprite> thermalb_taped_nailed{};
  P<Sprite> board{};
  P<Sprite> board_taped{};
  P<Sprite> board_nailed{};
  P<Sprite> board_taped_nailed{};
  P<Sprite> destroyed_taped{};
  P<Sprite> destroyed_nailed{};
  P<Sprite> destroyed_taped_nailed{};
  // ---- constructors
  LocationBathroomWindow() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void yesUndo2();
  void removeIfBroken(bool hadNails = false);
  void yesUndo();
  void yesTaped();
  void yesNailed();
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
