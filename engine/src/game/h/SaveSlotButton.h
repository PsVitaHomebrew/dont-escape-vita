// Generated from SaveSlotButton.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SaveSlotButton.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class SaveSlotButton : public ObjectActionController {
public:
  // ---- fields
  P<Sprite> thumb{};
  P<Sprite> bigThumb{};
  bool saveMode{};
  String slotName{};
  P<SpriteRenderer> bigSpriteRenderer{};
  P<SpriteRenderer> thumbSpriteRenderer{};
  Vector2 gts = Vector2(16.0f, 55.0f);
  Vector2 position = Vector2(16.0f, 55.0f);
  P<TextFieldController> labelSlotName{};
  P<TextFieldController> labelSlotDay{};
  P<TextFieldController> labelSlotDate{};
  P<AudioSource> audioSource{};
  // ---- constructors
  SaveSlotButton() {}
  // ---- methods
  void Start();
  void Update();
  void OnMouseEnter();
  void mouseOver() override;
  void mouseOut() override;
  void clickAction() override;
  void cancel();
  void overwriteSave();
  void loadSave();
  void updateState() override;
  void clickAction2() override;
  void clickAction0() override;
  void whatOnClick0() override;
  void whatOnClick() override;
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
