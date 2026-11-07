// Generated from PlayerController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/PlayerController.cpp
#pragma once
#include "../game_types.h"

class PlayerController : public MonoBehaviour {
public:
  using DialogueState = PlayerController_DialogueState;
  // ---- fields
  LayerMask blockingLayer{};
  bool clickedSomething{};
  bool clickedAlreadyForSomething{};
  P<BoxCollider2D> boxCollider{};
  P<Rigidbody2D> rb2D{};
  float SKEWFY{};
  PlayerController_DialogueState dialogue{};
  P<GameObject> currentDialogue{};
  String spawnName{};
  bool antiSoftLock = true;
  P<TextFieldController> textField{};
  P<AudioSource> aS{};
  static P<PlayerController> pc;
  static P<WalkController> wc;
  static P<StepSoundGenerator> ssg;
  bool npcShouldAppearRightOnSpot{};
  P<LocationManager> currentLocationManager{};
  bool allowDrop = true;
  Vector2 prevTargetClick{};
  float runTimeout{};
  P<SpriteRenderer> sr{};
  int softlockProbe{};
  float softlockTimer{};
  // ---- constructors
  PlayerController() {}
  // ---- methods
  void Awake();
  void Start();
  void say(String txt);
  void sayLine(String txt);
  void copySettingsToNPCs();
  void setDialogue(P<GameObject> target);
  void setBusy(bool busy);
  void forceAnimation(String name);
  void haltSoftLockProbe();
  void resumeSoftLockProbe();
  void Update();
  void interruptDialogueProbablyToKillPlayer();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
