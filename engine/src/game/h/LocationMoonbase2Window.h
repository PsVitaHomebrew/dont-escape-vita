// Generated from LocationMoonbase2Window.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationMoonbase2Window.cpp
#pragma once
#include "../game_types.h"

class LocationMoonbase2Window : public MonoBehaviour {
public:
  // ---- constructors
  LocationMoonbase2Window() {}
  // ---- methods
  void Start();
  void Update();
  void crack();
  void sound1();
  void sound2();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
