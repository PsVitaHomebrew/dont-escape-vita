// Generated from DreamGearsController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DreamGearsController.cpp
#pragma once
#include "../game_types.h"

class DreamGearsController : public MonoBehaviour {
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
  DreamGearsController() {}
  // ---- methods
  void Start();
  void show();
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
