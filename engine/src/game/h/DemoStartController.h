// Generated from DemoStartController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DemoStartController.cpp
#pragma once
#include "../game_types.h"

class DemoStartController : public MonoBehaviour {
public:
  // ---- constructors
  DemoStartController() {}
  // ---- methods
  void Start();
  void launch();
  void yesClick();
  void newGame(String param);
  void noClick();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
