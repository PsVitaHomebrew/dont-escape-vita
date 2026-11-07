// Generated from LoadingScene.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LoadingScene.cpp
#pragma once
#include "../game_types.h"

class LoadingScene : public MonoBehaviour {
public:
  // ---- fields
  float pyk{};
  String loadingTxt{};
  String addonTxt1{};
  String addonTxt2{};
  int dot{};
  bool doneanddone{};
  P<TextFieldController> tfc{};
  // ---- constructors
  LoadingScene() {}
  // ---- methods
  void Start();
  String ToHex(Array<uint8_t> bytes);
  void setRes();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
