// Generated from GameDataController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/GameDataController.cpp
#pragma once
#include "../game_types.h"

class GameDataController : public MonoBehaviour {
public:
  // ---- fields
  static P<GameDataController> gd;
  static P<PersistentData> persistentData;
  P<PersistentData> persistentDataView{};
  static String VERSION;
  static bool STEAM;
  static bool GOG;
  static bool KART;
  static String AUTOSAVE;
  static String CONTINUE;
  static String CHAPTER_1_COMPLETE_AUTOSAVE;
  static String CHAPTER_2_COMPLETE_AUTOSAVE;
  static String CHAPTER_3_COMPLETE_AUTOSAVE;
  static String CHAPTER_4_COMPLETE_AUTOSAVE;
  String equipped = String(u"");
  List<P<ItemData>> items{};
  List<P<Objective>> objectives{};
  List<P<Objective>> journals{};
  List<P<Objective>> visited{};
  int gameTime{};
  int timeLimit{};
  int traveledTime{};
  int workedTime{};
  String location{};
  String usedSpawner{};
  int currentX{};
  int currentY{};
  int previousX{};
  int previousY{};
  String previousLocation{};
  String finishingLocation{};
  static bool wantSave;
  String journalEntries = String(u"");
  String newJournalEntries = String(u"");
  static int MAX_FUEL;
  // ---- constructors
  GameDataController() {}
  // ---- methods
  void Awake();
  static void Achievement(String id);
  void Start();
  void updateAchievements();
  void Update();
  int getRandomHash(int len = 9);
  void newGame();
  bool getObjective(String id);
  int getObjectiveDetail(String id);
  bool getJournal(String id);
  int getJournalDetail(String id);
  void setJournal(String id, bool state);
  void setJournalDetail(String id, int detail);
  int getObjectiveIndex(String id);
  void setObjective(String id, bool state);
  bool saveIfOK(String sciezka = S(""));
  bool isOKtoSave(String sciezka);
  void setObjectiveDetail(String id, int detail);
  P<ItemData> getItemData(String id);
  void autoSave();
  void PersistentSave();
  void PersistentLoad();
  void initPersistantAchieves();
  void Save(String path);
  void politeLoad(String path);
  void tryLoad(String path, bool autosaveInstead = false);
  bool checkSave(String path);
  P<SaveData> getSavePreview(String path);
  bool Load(String path);
  int getCurrentDay();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
