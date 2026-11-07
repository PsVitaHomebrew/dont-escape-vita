// Generated from BarnPump.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BarnPump.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BarnPump : public ObjectActionController {
public:
  // ---- fields
  P<AudioClip> engineStart{};
  P<AudioClip> engineDie{};
  P<AudioClip> engineRun{};
  P<AudioSource> aS{};
  P<GameObject> lights{};
  P<GameObject> am1{};
  P<GameObject> am2{};
  // ---- constructors
  BarnPump() {}
  // ---- methods
  void Start();
  void updateState() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  void clickAction() override;
  void restore();
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
