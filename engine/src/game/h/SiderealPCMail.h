// Generated from SiderealPCMail.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SiderealPCMail.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SiderealPCMail : public ObjectActionController {
public:
  // ---- fields
  P<SpriteRenderer> spriter{};
  P<SiderealComputerSound> beeper{};
  P<Sprite> icon{};
  P<Sprite> window{};
  P<WorldCaption> mailCaption{};
  P<WorldCaption> mail{};
  P<WorldCaption> iconCaption{};
  P<Button> buttonLeft{};
  P<Button> buttonRight{};
  P<Button> buttonAtt{};
  P<WorldCaption> pageNumber{};
  P<Sprite> errorImg{};
  P<Sprite> mapLodge{};
  P<Sprite> mapBase{};
  P<Sprite> mailNorml{};
  P<Sprite> mailRead{};
  // ---- constructors
  SiderealPCMail() {}
  // ---- methods
  void Start();
  void Update();
  void showAtt();
  void makeItAtt1();
  void seenLodge();
  void seenBase();
  void nextPage();
  void makeItNext();
  void prevPage();
  void makeItPrev();
  void whatOnClick() override;
  void clickAction() override;
  void makeItSo2();
  void makeItSo();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
