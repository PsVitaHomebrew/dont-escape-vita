// Generated from DreamWraith.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DreamWraith.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class DreamWraith : public ObjectActionController {
public:
  // ---- fields
  P<GameObject> sarge{};
  P<LocationDream3BStart> ld3bs{};
  P<DialogueOptionController> doc{};
  P<TextFieldController> textField{};
  static Vector3 colorTiger; // = new Vector3(0.6f, 106f / 255f, 0.4f)  (set in _cctor)
  static Vector3 colorMaggie; // = new Vector3(0.6f, 106f / 255f, 0.4f)  (set in _cctor)
  Vector3 position{};
  Vector2 position2{};
  bool gogogo{};
  bool gogogo2{};
  P<SpriteShadow> shadow{};
  P<ParticleGenerator> playeremiter{};
  // ---- constructors
  DreamWraith() {}
  // ---- methods
  void Start();
  void whatOnClick0() override;
  void clickAction() override;
  void shadowpep(String val = S(""));
  void reset();
  void reset1();
  void reset2();
  void reset3();
  void reset4();
  void reset0();
  void Update();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  static void _cctor(); // translator: set the static fields marked (set in _cctor)
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
