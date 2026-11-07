// Generated from MapTextController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MapTextController.cpp
#pragma once
#include "../game_types.h"

class MapTextController : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> textfield{};
  // ---- constructors
  MapTextController() {}
  // ---- methods
  void Start();
  void Update();
  void updateTime();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
