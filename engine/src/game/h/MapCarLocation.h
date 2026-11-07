// Generated from MapCarLocation.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MapCarLocation.cpp
#pragma once
#include "../game_types.h"

class MapCarLocation : public MonoBehaviour {
public:
  // ---- fields
  List<P<GameObject>> carLocation{};
  // ---- constructors
  MapCarLocation() {}
  // ---- methods
  void Start();
  void Update();
  void hide();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
