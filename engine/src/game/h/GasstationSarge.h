// Generated from GasstationSarge.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationSarge.cpp
#pragma once
#include "../game_types.h"

class GasstationSarge : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  // ---- constructors
  GasstationSarge() {}
  // ---- methods
  void Start();
  void Update();
  void lookLeft();
  void lookRight();
  void shot();
  void decideRotation();
  void body_slam();
  void body_thud();
  void kneel();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
