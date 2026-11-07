// Generated from OptionsMenuStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/OptionsMenuStart.cpp
#pragma once
#include "../game_types.h"

class OptionsMenuStart : public MonoBehaviour {
public:
  // ---- fields
  P<TextFieldController> counter1{};
  P<TextFieldController> counter2{};
  P<TextFieldController> counter3{};
  P<TextFieldController> counter4{};
  List<P<AudioClip>> exampleSound{};
  P<AudioClip> exampleMusic{};
  P<AudioSource> aS{};
  P<DialogueOptionController> doc{};
  // ---- constructors
  OptionsMenuStart() {}
  // ---- methods
  void Start();
  void clearData();
  void yesClearData();
  void changeResolution(String res);
  void pickResolution();
  void quit();
  void quit2();
  void takeDoc(int i);
  void changeLanguage(String lang);
  void pickFont();
  void pickLanguage();
  void endTalk(String val = S(""));
  void resetGame2();
  void resetGame();
  void continueGame();
  void saveGame();
  void loadGame();
  void mainMenu();
  void staticUp();
  void staticDown();
  void speedUp();
  void speedDown();
  void musicUp();
  void musicDown();
  void soundsUp();
  void soundsDown();
  void Update();
  String meter(int stat);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
