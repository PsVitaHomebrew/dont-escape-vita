// Generated from Button.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Button.cpp
#pragma once
#include "../game_types.h"

class Button : public MonoBehaviour {
public:
  using Delegate = Button_Delegate;
  // ---- fields
  P<BoxCollider2D> bcol{};
  P<CursorController> cursorCont{};
  P<TextFieldController> buttonText{};
  P<AudioSource> audioSource{};
  bool workIfBusy = true;
  Vector3 color1{};
  Vector3 color2{};
  Vector3 background1{};
  Vector3 background2{};
  float alpha2{};
  float alpha1{};
  bool buttonEnabled = true;
  Button_Delegate onClick{};
  Button_Delegate onHover{};
  // ---- constructors
  Button() {}
  // ---- methods
  void Start();
  void Update();
  void OnMouseDown();
  void initButton(String label);
  void initCursor();
  void OnMouseOver();
  void OnMouseEnter();
  void OnMouseExit();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
