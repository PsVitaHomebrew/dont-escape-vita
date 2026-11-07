// Generated from LocationBaseUpstairsStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseUpstairsStart.cpp
#pragma once
#include "../game_types.h"

class LocationBaseUpstairsStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> szejk{};
  P<SpriteRenderer> holes{};
  P<SpriteRenderer> rays{};
  P<SpriteRenderer> rays2{};
  P<SpriteRenderer> darknessNormal{};
  P<SpriteRenderer> darknessNoRoof{};
  float aaa{};
  // ---- constructors
  LocationBaseUpstairsStart() {}
  // ---- methods
  void Start();
  void ignoreClicks(String a = S(""));
  void continueSleeping();
  void continueSleeping2(String val = S(""));
  void unlockPlayer2();
  void unlockPlayer();
  void fallKlapa();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
