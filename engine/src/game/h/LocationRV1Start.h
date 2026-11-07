// Generated from LocationRV1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationRV1Start.cpp
#pragma once
#include "../game_types.h"

class LocationRV1Start : public MonoBehaviour {
public:
  // ---- fields
  P<Sprite> snow{};
  P<Sprite> normal{};
  P<Sprite> scorch{};
  P<SpriteRenderer> sr{};
  bool codyLives{};
  bool codyTalked{};
  // ---- constructors
  LocationRV1Start() {}
  // ---- methods
  void Start();
  void checkCodyTalk();
  void Update();
  void grantAchievment(String s = S(""));
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
