// Generated from LocationBaseBathroomStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationBaseBathroomStart.cpp
#pragma once
#include "../game_types.h"

class LocationBaseBathroomStart : public MonoBehaviour {
public:
  // ---- fields
  P<Sprite> ded{};
  P<SpriteRenderer> holes{};
  P<SpriteRenderer> rays{};
  P<SpriteRenderer> rays2{};
  // ---- constructors
  LocationBaseBathroomStart() {}
  // ---- methods
  void Start();
  void startTalk();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
