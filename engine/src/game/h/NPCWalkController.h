// Generated from NPCWalkController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/NPCWalkController.cpp
#pragma once
#include "../game_types.h"

class NPCWalkController : public MonoBehaviour {
public:
  using Direction = NPCWalkController_Direction;
  // ---- fields
  Vector2 targetXY{};
  P<AudioSource> audioSource{};
  float colorGreen = 1.0f;
  float colorRed = 1.0f;
  float colorBlue = 1.0f;
  float colorAlpha = 1.0f;
  int range = 1;
  LayerMask blockingLayer{};
  bool pathRestricted{};
  Vector2 currentXY{};
  Vector3 currentXY_screen_rounded{};
  Vector2 currentSpeed{};
  Vector2 previousXY{};
  Vector2 previous2XY{};
  bool walkedBefore{};
  bool busy{};
  bool spawned{};
  Vector2 actionTargetXY{};
  List<Vector2> path{};
  bool waitOneFrameBeforeWalking{};
  int offsetY{};
  P<ObjectActionController> onFinishWalking0{};
  P<ObjectActionController> onFinishWalking{};
  P<ObjectActionController> onFinishWalking2{};
  bool waitedOneFrameBeforeAction{};
  P<TextFieldController> textfield{};
  float lastIdle{};
  int letOneMoreAnimationBeforeBusy{};
  P<SpriteShadow> shadow{};
  int shadowOffsetY{};
  NPCWalkController_Direction dir{};
  NPCWalkController_Direction previousDir{};
  int dirChangeDelay{};
  P<BoxCollider2D> bc2d{};
  String currentAnimClip = String(u"");
  float speed = 2.5f;
  float MAX_SPEED = 2.5f;
  P<GameObject> tlo{};
  bool clickable = true;
  // ---- constructors
  NPCWalkController() {}
  // ---- methods
  void Start();
  Vector2 getTargetXY();
  void setFlipped(bool f);
  bool flipped();
  String getCurrentAnimClip();
  void setTargetV3(Vector3 targetPosition);
  void setTarget(List<Vector2> newTarget);
  void setTextFieldY(int y);
  void playSound(P<AudioClip> ac);
  void setSimpleTargetV3(Vector3 newTarget);
  void setSimpleTarget(Vector2 newTarget);
  void clearTarget();
  void animationStartAction();
  void animationAction();
  void otherAnimationAction();
  void setBusy(bool b);
  void animationEnd();
  void setShadowOffset(int off);
  void forceAnimationForAnimationEvent(String name);
  void forceAnimationForAnimationEvent2(String name, bool flip);
  void forceAnimation(String name, bool flip = false, bool useCurrentDir = false, bool makeBusy = true);
  void Update();
  void updateStateAfterAnimation();
  void setAnimationTargetXY(String coords);
  void forceDirection(NPCWalkController_Direction d);
  void fullStop(bool abortTargetAction = false);
  void playIdleAnimation(String animationName);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
