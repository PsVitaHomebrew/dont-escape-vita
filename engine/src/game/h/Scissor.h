// Generated from Scissor.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Scissor.cpp
#pragma once
#include "../game_types.h"

class Scissor : public MonoBehaviour {
public:
  // ---- fields
  Rect scissorRect = Rect(0.0f, 0.0f, 1.0f, 1.0f);
  // ---- constructors
  Scissor() {}
  // ---- methods
  static void SetScissorRect(P<Camera> cam, Rect r);
  void OnPreRender();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
