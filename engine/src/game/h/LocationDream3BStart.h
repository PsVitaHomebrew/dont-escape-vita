// Generated from LocationDream3BStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDream3BStart.cpp
#pragma once
#include "../game_types.h"

class LocationDream3BStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> plane0bla{};
  P<SpriteRenderer> plane01{};
  P<SpriteRenderer> plane01bed{};
  P<SpriteRenderer> dream_stairs_front{};
  float alpha{};
  float alpha1{};
  float alpha2{};
  P<ObjectZController> zc1{};
  P<ObjectZController> zc2{};
  // ---- constructors
  LocationDream3BStart() {}
  // ---- methods
  void Start();
  void reset();
  void walkThere1();
  void walkThere();
  void unlock();
  void unlockThings(String param);
  void unlockThings2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
