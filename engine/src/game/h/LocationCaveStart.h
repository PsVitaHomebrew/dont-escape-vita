// Generated from LocationCaveStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCaveStart.cpp
#pragma once
#include "../game_types.h"

class LocationCaveStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> flag{};
  P<SpriteRenderer> blanket{};
  P<SpriteRenderer> blanketb{};
  P<SpriteRenderer> thermb{};
  P<SpriteRenderer> light1{};
  P<SpriteRenderer> light2{};
  bool codyLives{};
  bool codyTalked{};
  // ---- constructors
  LocationCaveStart() {}
  // ---- methods
  void Start();
  void Update();
  void grantAchievment(String s = S(""));
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
