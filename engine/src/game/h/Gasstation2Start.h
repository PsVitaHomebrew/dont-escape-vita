// Generated from Gasstation2Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Gasstation2Start.cpp
#pragma once
#include "../game_types.h"

class Gasstation2Start : public MonoBehaviour {
public:
  // ---- fields
  P<GasstationThug2Controller> thug2Controller{};
  P<GasstationThug2Controller> thug3Controller{};
  P<GasstationSarge> sargeController{};
  P<TextFieldController> sarge{};
  P<TextFieldController> thug{};
  Vector3 sargeColor{};
  Vector3 thugColor{};
  P<SpriteRenderer> snowr{};
  P<PolygonCollider2D> bikeBlock{};
  P<PolygonCollider2D> sargeBlock{};
  P<SpriteRenderer> bike{};
  bool updateDontKillCPUplz{};
  // ---- constructors
  Gasstation2Start() {}
  // ---- methods
  void Start();
  void starter();
  void thug2Go(String param = S(""));
  void forceTalk0();
  void forceTalk1();
  void sargeKneel(String param = S(""));
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
