// Generated from ExamineSprite.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ExamineSprite.cpp
#pragma once
#include "../game_types.h"

class ExamineSprite : public MonoBehaviour {
public:
  using Delegate = ExamineSprite_Delegate;
  // ---- fields
  static P<ExamineSprite> es;
  P<SpriteRenderer> spriteRenderer{};
  P<SpriteRenderer> spriteRenderer1{};
  P<SpriteRenderer> spriteRenderer2{};
  P<SpriteRenderer> spriteRenderer3{};
  P<SpriteRenderer> spriteRenderer4{};
  ExamineSprite_Delegate lookAction{};
  bool actionOnShow{};
  float alpha{};
  float targetAlpha{};
  bool active{};
  P<TextFieldController> textField{};
  List<String> pages{};
  int twidth{};
  float talpha{};
  Vector3 colors1{};
  Vector3 colors2{};
  String closingAnimation{};
  bool closingAnimationFlip{};
  bool cycleSprites{};
  bool quick = true;
  P<AudioClip> ac{};
  float audioVolume = 1.0f;
  // ---- constructors
  ExamineSprite() {}
  // ---- properties
  bool get_Active();
  // ---- methods
  void Awake();
  void Start();
  void initTextfield();
  void Update();
  void show(P<Sprite> sprite, P<Sprite> sprite1 = nullptr, P<Sprite> sprite2 = nullptr, P<Sprite> sprite3 = nullptr, P<Sprite> sprite4 = nullptr, ExamineSprite_Delegate act = nullptr, bool actionOnOpen = true);
  bool showPage();
  void readyText(List<String> _pages, int w, float r1, float g1, float b1, float r2, float g2, float b2, float _talpha);
  void hide();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
