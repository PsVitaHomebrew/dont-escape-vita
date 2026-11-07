// Generated from BaseFuelBasket.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/BaseFuelBasket.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class BaseFuelBasket : public ObjectActionController {
public:
  // ---- fields
  P<ParticleGenerator> smoke{};
  P<Sprite> wood1{};
  P<Sprite> wood2{};
  P<Sprite> wood3{};
  P<Sprite> wood4{};
  P<Sprite> wood0{};
  P<SpriteRenderer> wood{};
  P<SpriteRenderer> charcoal{};
  P<SpriteRenderer> charcoal_bag{};
  P<SpriteRenderer> cash{};
  P<SpriteRenderer> note{};
  P<SpriteRenderer> papers{};
  // ---- constructors
  BaseFuelBasket() {}
  // ---- methods
  void Start();
  void Update();
  void standSay();
  void kneel();
  void talk(String say);
  void whatOnClick0() override;
  void getup(String param = S(""));
  void talkAndGetUp(String say);
  void clickAction() override;
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
