// Generated from ProgressBarController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ProgressBarController.cpp
#pragma once
#include "../game_types.h"

class ProgressBarController : public MonoBehaviour {
public:
  // ---- fields
  float delay{};
  float percent{};
  int total = 1000;
  int current = 1000;
  int visibleCurrent{};
  P<SpriteRenderer> sr{};
  P<GameObject> bar{};
  P<GameObject> lifeLine{};
  P<TextFieldController> tf{};
  int timeToUpdateText = 1;
  float surv{};
  int dayWeFace{};
  // ---- constructors
  ProgressBarController() {}
  // ---- methods
  void Start();
  void Update();
  void setValue(int target);
  void updateView(bool updateText = false);
  Vector3 coords(Vector2 source);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
