// Generated from Location1Start.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/Location1Start.cpp
#pragma once
#include "../game_types.h"

class Location1Start : public MonoBehaviour {
public:
  // ---- fields
  P<SpriteRenderer> fireLight{};
  P<SpriteRenderer> fireLight2{};
  P<Sprite> memoryOfCrossroad{};
  P<Sprite> darkShadow{};
  P<Sprite> lightShadow{};
  P<Material> normalMat{};
  P<Material> lightMat{};
  P<SpriteRenderer> shadowrenderer{};
  bool memoryGo{};
  // ---- constructors
  Location1Start() {}
  // ---- methods
  void Start();
  void davidStand(String s = S(""));
  void decideShadows();
  void showMemoryOfCrossroad(String param);
  void initStory();
  void Update();
  void clockShow(String param);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
