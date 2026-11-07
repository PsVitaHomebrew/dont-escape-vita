// Generated from WaypointRVCave.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/WaypointRVCave.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class WaypointRVCave : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> klapaFlag{};
  P<Sprite> klapaBlanket{};
  P<Sprite> klapaBlanketb{};
  P<Sprite> klapaThermb{};
  String whatYouGet = String(u"");
  // ---- constructors
  WaypointRVCave() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void doPut();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
