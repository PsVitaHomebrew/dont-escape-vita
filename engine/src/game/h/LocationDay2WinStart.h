// Generated from LocationDay2WinStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationDay2WinStart.cpp
#pragma once
#include "../game_types.h"

class LocationDay2WinStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationDay2WinStart() {}
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
