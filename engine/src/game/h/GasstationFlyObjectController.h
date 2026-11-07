// Generated from GasstationFlyObjectController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationFlyObjectController.cpp
#pragma once
#include "../game_types.h"

class GasstationFlyObjectController : public MonoBehaviour {
public:
  // ---- fields
  bool flying{};
  float realX{};
  float realY{};
  // ---- constructors
  GasstationFlyObjectController() {}
  // ---- methods
  void Start();
  void Update();
  void fly(P<Item> item);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
