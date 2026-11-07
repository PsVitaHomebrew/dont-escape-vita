// Generated from CraneCables.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/CraneCables.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class CraneCables : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> cord{};
  P<Sprite> stormcatcher_on{};
  P<Sprite> stormcatcher_off{};
  P<SpriteRenderer> glow{};
  P<GameObject> sparks{};
  // ---- constructors
  CraneCables() {}
  // ---- methods
  void Start();
  void Update();
  void clickAction() override;
  void stopSparks();
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
