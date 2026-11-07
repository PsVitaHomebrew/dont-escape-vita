// Generated from LetterFall.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LetterFall.cpp
#pragma once
#include "../game_types.h"

class LetterFall : public MonoBehaviour {
public:
  // ---- fields
  P<ParticleGenerator> sandMove1{};
  P<ParticleGenerator> sandMove2{};
  P<ParticleGenerator> sandMove3{};
  P<ParticleGenerator> sandMove4{};
  P<ParticleGenerator> sandFall1{};
  P<ParticleGenerator> sandFall2{};
  P<ParticleGenerator> sandFall3{};
  P<ParticleGenerator> sandFall4{};
  P<ParticleGenerator> sandLauch{};
  P<Npc2Controller> barry{};
  P<NPCWalkController> barryW{};
  P<NPCWalkController> codyW{};
  P<GameObject> barryJumpTarget{};
  P<GameObject> barryJumpSource{};
  P<GameObject> playerJumpTarget{};
  P<GameObject> playerJumpSource{};
  P<AudioSource> aS{};
  P<GameObject> codyRunSource{};
  P<GameObject> codyRunTarget{};
  P<GameObject> codyJumpTarget{};
  P<NPCWalkController> gingerW{};
  P<GameObject> gingerJumpSource{};
  P<GameObject> gingerJumpTarget{};
  P<SpriteRenderer> barLow{};
  // ---- constructors
  LetterFall() {}
  // ---- methods
  void Start();
  void startTalkAfterfall();
  void kneel(String a = S(""));
  void kneelEnd(String a = S(""));
  void Update();
  void quickFall();
  void hideAndWait();
  void showBelka();
  void showBelka2();
  void startAnim(String a = S(""));
  void gingerWindUp();
  void gingerJump();
  void playerJump();
  void swingLoop();
  void prepare();
  void codyRun();
  void codyJump();
  void piachSyp();
  void barryWindUp();
  void barryJump();
  void startLaunch();
  void endLaunch();
  void startSandMove();
  void stopSandMove();
  void startSandFall();
  void stopSandFall();
  void endAnim();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
