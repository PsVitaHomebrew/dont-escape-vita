// Generated from Moonbase2Computer.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Moonbase2Computer.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Moonbase2Computer : public ObjectActionController {
public:
  // ---- fields
  P<MoonbaseLightFlicker> mlf{};
  P<Sprite> screen{};
  // ---- constructors
  Moonbase2Computer() {}
  // ---- methods
  void updateMLF();
  void Start();
  void pressit(String s = S(""));
  void pressit2();
  void pressit3();
  void scansound();
  void failsound(String s = S(""));
  void successsound(String s = S(""));
  void successsound2(String s = S(""));
  void scanfail();
  void clickAction() override;
  void scansuccess();
  void scansuccess2();
  void whatOnClick0() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
