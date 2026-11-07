// Generated from SaveData.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SaveData.cpp
#pragma once
#include "../game_types.h"

class SaveData : public Obj {
public:
  // ---- fields
  int gameTime{};
  int timeLimit{};
  int traveledTime{};
  int workedTime{};
  int gameDay{};
  DateTime dateTime{};
  List<P<ItemData>> items{};
  List<P<Objective>> objectives{};
  List<P<Objective>> journals{};
  List<P<Objective>> visited{};
  int currentX{};
  int currentY{};
  String location{};
  String usedSpawner{};
  int previousX{};
  int previousY{};
  String previousLocation{};
  String finishingLocation{};
  String journalEntries{};
  // ---- constructors
  SaveData() {}
  // ---- generated
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
