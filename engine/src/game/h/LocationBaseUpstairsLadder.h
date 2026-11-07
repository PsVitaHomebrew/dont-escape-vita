// Generated from LocationBaseUpstairsLadder.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseUpstairsLadder.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationBaseUpstairsLadder : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> klapa{};
  P<Sprite> klapaFlag{};
  P<Sprite> klapaBlanket{};
  P<Sprite> klapaBlanketb{};
  P<Sprite> klapaThermb{};
  P<Sprite> klapa2{};
  P<Sprite> klapaFlag2{};
  P<Sprite> klapaBlanket2{};
  P<Sprite> klapaBlanketb2{};
  P<Sprite> klapaThermb2{};
  // ---- constructors
  LocationBaseUpstairsLadder() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void whatOnClick() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
