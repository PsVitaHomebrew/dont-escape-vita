// Generated from LocationDreamBugsStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDreamBugsStart.cpp
#pragma once
#include "../game_types.h"

class LocationDreamBugsStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> plane0bla{};
  P<SpriteRenderer> plane01{};
  P<SpriteRenderer> window{};
  float alpha{};
  float alpha1{};
  // ---- constructors
  LocationDreamBugsStart() {}
  // ---- methods
  void Start();
  void walkThere1();
  void walkThere();
  void unlock();
  void sayDots(String p = S(""));
  void unlockThings(String param);
  void unlockThings2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
