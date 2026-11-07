// Generated from CurtainController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CurtainController.cpp
#pragma once
#include "../game_types.h"

class CurtainController : public MonoBehaviour {
public:
  using Delegate = CurtainController_Delegate;
  // ---- fields
  float alpha = 1.0f;
  float targetAlpha = 1.0f;
  float speed = 0.025f;
  int delayer{};
  float timeout{};
  static float NORMAL_CURTAIN_SPEED;
  static float MENU_CURTAIN_SPEED;
  static P<CurtainController> cc;
  CurtainController_Delegate onSceneChange{};
  String targetLocaiton = String(u"");
  String nextSceneStartAnimation{};
  bool nextSceneStartAnimatioFlip{};
  P<AudioClip> nextSceneStartSound{};
  WalkController_Direction targetWalkDir{};
  P<LocationManager> currentLocationManager{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  CurtainController() {}
  // ---- methods
  void Awake();
  void Start();
  float getAlpha();
  bool okToGo();
  void loadAfterWhile();
  void updatePreviousLocation();
  void Update();
  void loadScene(String name);
  void OnLevelWasLoaded(int level);
  void fadeOut(String target = S("none"), WalkController_Direction targetDir = WalkController_Direction::NULL_, String animation = nullptr, P<AudioClip> sound = nullptr, bool flipX = false, CurtainController_Delegate actionAfterFade = nullptr, float tSpeed = 0.05f);
  static void fixCameraRect();
  void fadeIn();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
