// Generated from LocationEndGoodStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationEndGoodStart.cpp
#pragma once
#include "../game_types.h"

class LocationEndGoodStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> cody00{};
  P<SpriteRenderer> cody01{};
  P<SpriteRenderer> cody02{};
  P<SpriteRenderer> cody03{};
  P<SpriteRenderer> cody04{};
  P<SpriteRenderer> cody05{};
  P<SpriteRenderer> barry00{};
  P<SpriteRenderer> barry01{};
  P<SpriteRenderer> barry02{};
  P<SpriteRenderer> barry03{};
  P<SpriteRenderer> cate00{};
  P<SpriteRenderer> cate01{};
  P<SpriteRenderer> cate02{};
  P<SpriteRenderer> cate03{};
  P<SpriteRenderer> cate04{};
  P<SpriteRenderer> cate05{};
  P<SpriteRenderer> david00{};
  P<SpriteRenderer> david01{};
  P<SpriteRenderer> david02{};
  P<SpriteRenderer> david03{};
  P<SpriteRenderer> david04{};
  P<SpriteRenderer> end{};
  P<TextFieldController> napis1{};
  P<TextFieldController> napis2{};
  P<SpriteRenderer> fadeIn{};
  P<SpriteRenderer> fadeIn2{};
  P<SpriteRenderer> fadeOut{};
  P<SpriteRenderer> fadeOut2{};
  float adoptionX = -0.156f;
  float waiting{};
  int skipit{};
  float timer{};
  float totalTime{};
  // ---- constructors
  LocationEndGoodStart() {}
  // ---- methods
  void Start();
  void mainMenu();
  void napisy();
  void cumulInvoke(String methodName, float time);
  void fader(P<SpriteRenderer> sr);
  void music();
  void music2();
  void slice_david00();
  void slice_david01();
  void slice_david02();
  void slice_david03();
  void slice_david04();
  void slice_cate00();
  void slice_cate01();
  void slice_cate02();
  void slice_cate03();
  void slice_cate04();
  void slice_cate05();
  void slice_barry00();
  void slice_barry01();
  void slice_barry02();
  void slice_barry03();
  void slice_cody00();
  void slice_cody01();
  void slice_cody02();
  void slice_cody03();
  void slice_cody04();
  void slice_cody05();
  void slice_end();
  void Update();
  void showButton();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
