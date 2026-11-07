// Generated from Item.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Item.cpp
#pragma once
#include "../game_types.h"

class Item : public Obj {
public:
  // ---- fields
  String id{};
  float weight{};
  P<AudioClip> sound{};
  P<AudioClip> soundLoop{};
  P<Sprite> inventorySprite{};
  P<Sprite> groundSprite{};
  P<Sprite> groundSprite_1{};
  P<Sprite> groundSprite_2{};
  P<Sprite> groundSprite_3{};
  P<Sprite> groundSprite_4{};
  P<Sprite> groundSprite_5{};
  int animationDelay{};
  P<Sprite> examineSprite{};
  P<Sprite> examineSprite_1{};
  P<Sprite> examineSprite_2{};
  P<Sprite> examineSprite_3{};
  P<Sprite> examineSprite_4{};
  bool examineCycleSprites{};
  List<String> examineTexts{};
  int textWidth{};
  int textShiftX{};
  int textShiftY{};
  Color textColor1{};
  Color textColor2{};
  P<ItemData> dataRef{};
  List<P<ItemInteraction>> usableItemsInventory{};
  List<P<ItemInteraction>> usableItemsGround{};
  ExamineSprite_Delegate lookAction{};
  bool actionOnLook{};
  // ---- constructors
  Item() {}
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
