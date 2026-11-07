// Generated from WorldCaption.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/WorldCaption.cpp
#pragma once
#include "../game_types.h"

class WorldCaption : public MonoBehaviour {
public:
  // ---- fields
  String nameToDisplay{};
  String overrideString = String(u"");
  float r{};
  float g{};
  float b{};
  int width{};
  P<TextFieldController> t{};
  // ---- constructors
  WorldCaption() {}
  // ---- methods
  void Start();
  void Update();
  void manualUpdate();
  void hide();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
