// Generated from WalkController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/WalkController.cpp
#pragma once
#include "../game_types.h"

class WalkController : public MonoBehaviour {
public:
  using Delegate = WalkController_Delegate;
  using Direction = WalkController_Direction;
  // ---- fields
  Vector2 targetXY{};
  List<Vector2> path{};
  int range = 1;
  Vector2 currentXY{};
  Vector3 currentXY_screen_rounded{};
  Vector2 currentSpeed{};
  bool walkedBefore{};
  bool busy{};
  bool waitOneFrameBeforeWalking{};
  int offsetY{};
  P<ObjectActionController> onFinishWalking0{};
  P<ObjectActionController> onFinishWalking{};
  P<ObjectActionController> onFinishWalking2{};
  bool waitedOneFrameBeforeAction{};
  WalkController_Delegate autoAction{};
  float lastIdle{};
  int letOneMoreAnimationBeforeBusy{};
  P<SpriteShadow> shadow{};
  int shadowOffsetY{};
  WalkController_Direction dir{};
  WalkController_Direction previousDir{};
  int dirChangeDelay{};
  String currentAnimClip = String(u"");
  float speed = 2.5f;
  float speedMultip = 1.0f;
  float MAX_SPEED = 2.5f;
  P<SpriteRenderer> sr{};
  P<ParticleGenerator> dustPart{};
  P<Animator> animator{};
  P<GameObject> tlo{};
  bool suit{};
  // ---- constructors
  WalkController() {}
  // ---- methods
  Vector2 getFinalTarget();
  void Start();
  void setTextFieldY(int y);
  String getCurrentAnimClip();
  void setCurrentAnimClip(String anim);
  void setTarget(List<Vector2> newTarget);
  void setSimpleTargetV3(Vector3 targetPosition);
  void setSimpleTarget(Vector2 newTarget);
  void clearTarget();
  void animationStartAction();
  void animationAction();
  void otherAnimationAction();
  void animationEnd();
  void setShadowOffset(int off);
  void forceAnimationForAnimationEvent(String name);
  void forceAnimationForAnimationEventFlipped(String name);
  void forceAnimation(String name, bool flip = false, bool useCurrentDir = false, bool makeBusy = true);
  void playSound(P<AudioClip> ac);
  void Update();
  void forceDirection(WalkController_Direction d);
  void fullStop(bool abortTargetAction = false, bool playStandAnimation = true, bool forceStandAnimation = false);
  void playIdleAnimation(String animationName);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
