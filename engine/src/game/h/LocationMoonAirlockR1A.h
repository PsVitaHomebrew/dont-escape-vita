// Generated from LocationMoonAirlockR1A.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonAirlockR1A.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationMoonAirlockR1A : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  bool left{};
  int number{};
  P<AudioSource> audioSource{};
  List<P<Sprite>> sprites{};
  // ---- constructors
  LocationMoonAirlockR1A() {}
  // ---- methods
  void Start();
  void leave();
  void doorop();
  void unlock();
  void clickAction() override;
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
