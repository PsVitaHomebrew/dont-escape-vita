// Generated from LocationCaveHeaterOrFan.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationCaveHeaterOrFan.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class LocationCaveHeaterOrFan : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> fanstill{};
  P<SpriteRenderer> fango{};
  P<SpriteRenderer> heater{};
  P<SpriteRenderer> heaterGlow{};
  float lightAlfa{};
  float lightAlfa2{};
  P<AudioClip> fanSound{};
  P<AudioClip> heaterSound{};
  // ---- constructors
  LocationCaveHeaterOrFan() {}
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
