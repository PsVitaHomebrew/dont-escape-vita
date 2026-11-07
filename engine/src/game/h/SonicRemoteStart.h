// Generated from SonicRemoteStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SonicRemoteStart.cpp
#pragma once
#include "../game_types.h"

class SonicRemoteStart : public MonoBehaviour {
public:
  // ---- constructors
  SonicRemoteStart() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
