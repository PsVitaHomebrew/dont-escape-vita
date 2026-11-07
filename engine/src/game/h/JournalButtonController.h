// Generated from JournalButtonController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/JournalButtonController.cpp
#pragma once
#include "../game_types.h"

class JournalButtonController : public MonoBehaviour {
public:
  // ---- fields
  P<InventoryController> inventory{};
  String frame_name_sufix = S("0");
  String frame_name_prefix = S("journal_");
  P<Animator> exc{};
  Vector2 pozycja{};
  P<SpriteRenderer> excSprite{};
  // ---- constructors
  JournalButtonController() {}
  // ---- methods
  void Start();
  void showJournal(String param);
  void setWarning(bool yesno);
  void showFinal();
  void show();
  void hide();
  void Update();
  void OnMouseOver();
  void OnMouseExit();
  void fakeClick();
  void OnMouseDown();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
