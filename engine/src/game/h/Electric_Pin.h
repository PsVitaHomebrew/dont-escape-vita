// Generated from Electric_Pin.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Electric_Pin.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class Electric_Pin : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> wire_1{};
  P<Sprite> wire_2{};
  P<Sprite> wire_3{};
  P<Sprite> wire_4{};
  P<Sprite> wire_5{};
  P<ElectricPuzzleReset> butbut{};
  bool input{};
  bool output{};
  String pinLetter{};
  int pinNumber{};
  String prevPin{};
  P<Sprite> selector{};
  bool showValue{};
  int electricValue{};
  P<SpriteRenderer> sr{};
  // ---- constructors
  Electric_Pin() {}
  // ---- methods
  void Start();
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  void startWithCheck();
  void checkConnect(int exit, String pinName);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
