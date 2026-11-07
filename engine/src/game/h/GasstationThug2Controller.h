// Generated from GasstationThug2Controller.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GasstationThug2Controller.cpp
#pragma once
#include "../game_types.h"

class GasstationThug2Controller : public MonoBehaviour {
public:
  // ---- fields
  String nameId{};
  bool riding{};
  P<AudioSource> aS{};
  float truex{};
  float truey{};
  float speed{};
  // ---- constructors
  GasstationThug2Controller() {}
  // ---- methods
  void Start();
  void Update();
  void ride();
  void startMoving();
  void brrrr();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
