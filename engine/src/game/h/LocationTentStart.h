// Generated from LocationTentStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationTentStart.cpp
#pragma once
#include "../game_types.h"

class LocationTentStart : public MonoBehaviour {
public:
  // ---- constructors
  LocationTentStart() {}
  // ---- methods
  void Start();
  void exitTent();
  void exitTent3(String v = S(""));
  void exitTent4();
  void exitTent2();
  void keepStraight(String val = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
