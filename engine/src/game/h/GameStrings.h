// Generated from GameStrings.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GameStrings.cpp
#pragma once
#include "../game_types.h"

class GameStrings : public Obj {
public:
  using Language = GameStrings_Language;
  // ---- fields
  static Array<KeyValueString> gui;
  static Array<KeyValueString> items;
  static Array<KeyValueString> map;
  static Array<KeyValueString> objects;
  static Array<KeyValueString> journal;
  static Array<KeyValueString> actions;
  static Array<KeyValueString> warnings;
  static Array<KeyValueString> world_labels;
  static Array<KeyValueString> results;
  static Array<KeyValueString> dialogues;
  static Array<KeyValueString> languages;
  // ---- constructors
  GameStrings() {}
  // ---- methods
  static void readStrings(String lang);
  static Array<KeyValueString> parse(P<TextAsset> toParse);
  static String getPrefixedShort(Array<KeyValueString> lib, String what, bool capital = false);
  static String getWrongInteractionText();
  static String capitalise(String src);
  static String getString(Array<KeyValueString> lib, String key);
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
