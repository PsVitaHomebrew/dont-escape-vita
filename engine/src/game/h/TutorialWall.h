// Generated from TutorialWall.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TutorialWall.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TutorialWall : public ObjectActionController {
public:
  // ---- fields
  P<ParticleGenerator> smash1{};
  P<ParticleGenerator> smash2{};
  P<ParticleGenerator> smash3{};
  P<SpriteRenderer> sr{};
  P<Sprite> s1{};
  P<Sprite> s2{};
  P<Sprite> s3{};
  P<AudioSource> aS{};
  // ---- constructors
  TutorialWall() {}
  // ---- methods
  void Start();
  void creak1();
  void creak2();
  void creak3();
  void clickAction() override;
  void ssmash2();
  void ssmash3();
  void stopSmash1();
  void stopSmash2();
  void stopSmash3();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
