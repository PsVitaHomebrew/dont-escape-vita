// Generated from LocationOutpostOutside2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationOutpostOutside2Start.cpp
#pragma once
#include "../game_types.h"

class LocationOutpostOutside2Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> playerShadow{};
  P<GameObject> electro{};
  P<ParticleGenerator> smoke{};
  P<ParticleGenerator> sparks{};
  float modX{};
  float modY{};
  P<TextFieldController> scannerTxt{};
  // ---- constructors
  LocationOutpostOutside2Start() {}
  // ---- methods
  void Start();
  void Update();
  void doormat();
  void disableSparks();
  void resetStage();
  void doormatGo(String t = S(""));
  void letItGo();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
