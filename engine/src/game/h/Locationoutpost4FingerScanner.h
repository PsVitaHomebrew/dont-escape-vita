// Generated from Locationoutpost4FingerScanner.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Locationoutpost4FingerScanner.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Locationoutpost4FingerScanner : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> red{};
  P<Sprite> green{};
  // ---- constructors
  Locationoutpost4FingerScanner() {}
  // ---- methods
  void Start();
  void pressit(String s = S(""));
  void pressit2(String s = S(""));
  void pressit3(String s = S(""));
  void scansound();
  void failsound(String s = S(""));
  void successsound(String s = S(""));
  void scanfail();
  void scanfail2();
  void clickAction() override;
  void scansuccess();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
