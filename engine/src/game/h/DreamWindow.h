// Generated from DreamWindow.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/DreamWindow.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class DreamWindow : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> window{};
  Array<P<GameObject>> pajaki{};
  P<lightingblast> light{};
  // ---- constructors
  DreamWindow() {}
  // ---- methods
  void Start();
  void whatOnClick() override;
  void clickAction() override;
  void thunderstorm();
  void rainSmoke1();
  void rainSmoke2();
  void prestrike();
  void strike();
  void strikeEnd();
  void bangbangyouredead();
  void gasAfterWhile();
  void makeSmoke();
  void makeSmoke2();
  void makeSmoke3();
  void makeSmoke4();
  void updateState() override;
  void showBugs();
  void clickAction2() override;
  void nextScene();
  void nextScene2();
  void nextScene3();
  void startFuneral();
  void startDreamTalk();
  void transportToSidereal(String s = S(""));
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
