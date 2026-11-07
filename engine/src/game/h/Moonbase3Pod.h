// Generated from Moonbase3Pod.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Moonbase3Pod.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Moonbase3Pod : public ObjectActionController {
public:
  // ---- fields
  String whose{};
  String numerek{};
  P<GameObject> person{};
  P<AudioSource> audioSouruce2{};
  // ---- constructors
  Moonbase3Pod() {}
  // ---- methods
  void Start();
  bool waitForOthers();
  void makeSound();
  void failsound(String s = S(""));
  void clickAction() override;
  void enterPod();
  void openIfNeeded(bool close = false);
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
