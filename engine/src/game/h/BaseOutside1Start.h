// Generated from BaseOutside1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseOutside1Start.cpp
#pragma once
#include "../game_types.h"

class BaseOutside1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> heli{};
  P<SpriteRenderer> moon{};
  P<SpriteRenderer> moong{};
  P<Sprite> moon1{};
  P<Sprite> moon2{};
  P<Sprite> moon3{};
  P<Sprite> moon4{};
  P<Sprite> moon1g{};
  P<Sprite> moon2g{};
  P<Sprite> moon3g{};
  P<Sprite> moon4g{};
  P<NPCWalkController> cody{};
  P<GameObject> codyRun1{};
  P<GameObject> codyRun2{};
  P<GameObject> codyRun3{};
  P<SpriteRenderer> snow{};
  P<SpriteRenderer> bugs{};
  P<SpriteRenderer> coptercoat{};
  P<SpriteRenderer> roof{};
  P<SpriteRenderer> roof1{};
  P<SpriteRenderer> piorunochron{};
  float runState{};
  // ---- constructors
  BaseOutside1Start() {}
  // ---- methods
  void Start();
  void showIntro2();
  void showIntro1b();
  void Update();
  void d4Intro();
  void turnNorth2(String s = S(""));
  void turnNorth(String s = S(""));
  void runLikeCrazy(String s = S(""));
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
