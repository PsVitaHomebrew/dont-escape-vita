// Generated from OutpostRadarBeep.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OutpostRadarBeep.cpp
#pragma once
#include "../game_types.h"

class OutpostRadarBeep : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  P<AudioClip> radar{};
  // ---- constructors
  OutpostRadarBeep() {}
  // ---- methods
  void Start();
  void beep();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
