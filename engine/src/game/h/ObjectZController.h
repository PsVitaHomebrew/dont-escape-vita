// Generated from ObjectZController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ObjectZController.cpp
#pragma once
#include "../game_types.h"

class ObjectZController : public MonoBehaviour {
public:
  // ---- fields
  P<GameObject> parentObject{};
  float aa{};
  float bb{};
  float cc{};
  Vector3 vec1{};
  Vector3 vec2{};
  Vector3 vec3{};
  // ---- constructors
  ObjectZController() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
