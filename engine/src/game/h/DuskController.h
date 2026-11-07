// Generated from DuskController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DuskController.cpp
#pragma once
#include "../game_types.h"

class DuskController : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> sr{};
  P<Sprite> dusk1{};
  P<Sprite> dusk2{};
  P<Sprite> dusk3{};
  P<Sprite> dusk4{};
  P<Sprite> dusk5{};
  P<Sprite> dawn1{};
  P<Sprite> dawn2{};
  P<Sprite> dawn3{};
  P<Sprite> dawn4{};
  P<Sprite> dawn5{};
  P<Sprite> dawn6{};
  P<Material> ov{};
  P<Material> ml{};
  // ---- constructors
  DuskController() {}
  // ---- methods
  void Start();
  void Update();
  void manualUpdate();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
