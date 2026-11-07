// Generated from SaveMenuStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SaveMenuStart.cpp
#pragma once
#include "../game_types.h"

class SaveMenuStart : public MonoBehaviour {
public:
  // ---- constructors
  SaveMenuStart() {}
  // ---- methods
  void Start();
  void continueGame();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
