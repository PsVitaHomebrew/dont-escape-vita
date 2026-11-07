// Generated from DigitalNumber.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DigitalNumber.cpp
#pragma once
#include "../game_types.h"

class DigitalNumber : public MonoBehaviour {
public:
  // ---- fields
  Array<P<Sprite>> digits{};
  String dataSource{};
  int digit{};
  P<DigitalNumber> next{};
  P<DigitalNumber> prev{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  DigitalNumber() {}
  // ---- methods
  void Start();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
