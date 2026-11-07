// Generated from GearsController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GearsController.cpp
#pragma once
#include "../game_types.h"

class GearsController : public MonoBehaviour {
public:
  // ---- fields
  P<Sprite> normal{};
  P<Sprite> active{};
  float alpha = 1.0f;
  float alphaSpeed = 0.25f;
  bool visible = true;
  P<SpriteRenderer> spriteRenderer{};
  String condition{};
  String frame_name_sufix = S("0");
  // ---- constructors
  GearsController() {}
  // ---- methods
  void Start();
  void show();
  void showFinal();
  void hide();
  void showGears(bool fast = true);
  void Update();
  void OnMouseOver();
  void OnMouseExit();
  void OnMouseDown();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
