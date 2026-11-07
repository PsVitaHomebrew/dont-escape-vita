// Generated from LocationDay3WinStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay3WinStart.cpp
#pragma once
#include "../game_types.h"

class LocationDay3WinStart : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> noroof{};
  // ---- constructors
  LocationDay3WinStart() {}
  // ---- methods
  void Start();
  void continueGame(String param);
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
