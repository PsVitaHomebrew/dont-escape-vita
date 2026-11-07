// Generated from LocationOutpost5CardScanner.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpost5CardScanner.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationOutpost5CardScanner : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> red{};
  P<Sprite> green{};
  // ---- constructors
  LocationOutpost5CardScanner() {}
  // ---- methods
  void Start();
  void pressit(String s = S(""));
  void pressit2(String s = S(""));
  void scansound();
  void failsound(String s = S(""));
  void successsound(String s = S(""));
  void scanfail();
  void clickAction() override;
  void scansuccess();
  void updateState() override;
  void whatOnClick0() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
