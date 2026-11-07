// Generated from SiderealPCCaptionWhite.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealPCCaptionWhite.cpp
#pragma once
#include "../game_types.h"

class SiderealPCCaptionWhite : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  P<TextFieldController> t{};
  // ---- constructors
  SiderealPCCaptionWhite() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
