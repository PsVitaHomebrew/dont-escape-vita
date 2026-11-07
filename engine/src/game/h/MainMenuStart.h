// Generated from MainMenuStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/MainMenuStart.cpp
#pragma once
#include "../game_types.h"

class MainMenuStart : public MonoBehaviour {
public:
  // ---- fields
  String custom_disc{};
  String custom_d1{};
  String custom_d2{};
  String custom_d3{};
  String custom_d4{};
  P<Sprite> background1_a{};
  P<Sprite> background1_b{};
  P<Sprite> background2_a{};
  P<Sprite> background2_b{};
  P<Sprite> background3_a{};
  P<Sprite> background3_b{};
  P<TextFieldController> counter1{};
  P<TextFieldController> counter2{};
  P<TextFieldController> counter3{};
  P<SpriteRenderer> background_2_1{};
  P<SpriteRenderer> background_2_2{};
  P<SpriteRenderer> background_2_3{};
  P<SpriteRenderer> background_1_3{};
  P<ParticleGenerator> clouds{};
  P<DialogueOptionController> doc{};
  P<SpriteRenderer> back1{};
  P<SpriteRenderer> back2{};
  P<SpriteRenderer> fore1{};
  P<SpriteRenderer> fore2{};
  float xpos{};
  float alpha{};
  float previousAlpha = 999.0f;
  P<Button> continueBtn{};
  P<Button> newGameBtn{};
  P<Button> loadGameBtn{};
  P<Button> OptionsBtn{};
  P<Button> CreditsBtn{};
  P<Button> QuitBtn{};
  P<Button> fakeContinue1{};
  P<Button> fakeContinue2{};
  P<Button> fakeContinue3{};
  P<Button> fakeNewGame1{};
  P<Button> fakeNewGame2{};
  P<Button> fakeNewGame3{};
  P<Button> fakeLoadGame1{};
  P<Button> fakeLoadGame2{};
  P<Button> fakeLoadGame3{};
  P<Button> fakeOptions1{};
  P<Button> fakeOptions2{};
  P<Button> fakeOptions3{};
  P<Button> fakeCredits1{};
  P<Button> fakeCredits2{};
  P<Button> fakeCredits3{};
  P<Button> fakeQuit1{};
  P<Button> fakeQuit2{};
  P<Button> fakeQuit3{};
  P<ParticleGenerator> d_a_1{};
  P<ParticleGenerator> d_a_2{};
  P<ParticleGenerator> d_a_3{};
  P<ParticleGenerator> d_a_4{};
  P<ParticleGenerator> d_a_5{};
  P<ParticleGenerator> d_b_1{};
  P<ParticleGenerator> d_b_2{};
  P<ParticleGenerator> d_b_3{};
  P<ParticleGenerator> d_b_4{};
  P<ParticleGenerator> d_b_5{};
  float blinkDelay{};
  float blinkChance = 1.0f;
  bool old{};
  // ---- constructors
  MainMenuStart() {}
  // ---- methods
  void makeCloudsNormal();
  void setupButton(P<Button> button, P<Button> fake1, P<Button> fake2, P<Button> fake3, String label, Button_Delegate action);
  void Start();
  void creditsClick();
  void optionsClick();
  void loadGame();
  void continueGame();
  void quit();
  void noQuit();
  void quit2();
  void newGame();
  void newGameCustom();
  void newGameCustom1(String param = S(""));
  void newGameCustom2(String param = S(""));
  void newGameCustom3(String param = S(""));
  void newGameCustom4(String param = S(""));
  void newGameCustom5(String param = S(""));
  void newGameCustom6(String param = S(""));
  void takeDoc(int i);
  void pickDays(String lang);
  void endTalk(String val = S(""));
  void newGame2();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
