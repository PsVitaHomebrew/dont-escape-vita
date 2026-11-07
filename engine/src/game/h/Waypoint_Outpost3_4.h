// Generated from Waypoint_Outpost3_4.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Waypoint_Outpost3_4.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Waypoint_Outpost3_4 : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Animator> animator{};
  P<AudioSource> aS{};
  P<GameObject> actionRide{};
  P<GameObject> actionCall{};
  bool cickedAlready{};
  // ---- constructors
  Waypoint_Outpost3_4() {}
  // ---- methods
  void Start();
  void playAnimation(String param);
  void clickAction() override;
  void rideDown0();
  void rideDown();
  void updateState() override;
  void playSound(String soundName);
  void clickAction2() override;
  void clickAction0() override;
  void elevatorReady();
  void closeDoorInFive();
  void lookAtIt();
  void clickIt();
  void updateElevatorLogic();
  void closeDoorQuickAndFast();
  void closeDoorKindly();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
