// Generated from CS3Pack.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CS3Pack.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CS3Pack : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> pack{};
  P<SpriteRenderer> pack_hang{};
  P<GameObject> marker1{};
  P<GameObject> marker2{};
  P<GameObject> zmarker1{};
  P<GameObject> zmarker2{};
  P<Sprite> hook1a{};
  P<Sprite> hook1b{};
  P<Sprite> hook2a{};
  P<Sprite> hook2b{};
  P<SpriteRenderer> hook{};
  // ---- constructors
  CS3Pack() {}
  // ---- methods
  void Start();
  void Update();
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
