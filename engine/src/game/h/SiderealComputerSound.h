// Generated from SiderealComputerSound.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealComputerSound.cpp
#pragma once
#include "../game_types.h"

class SiderealComputerSound : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  List<P<AudioClip>> sounds{};
  // ---- constructors
  SiderealComputerSound() {}
  // ---- methods
  void Start();
  void Update();
  void beep();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
