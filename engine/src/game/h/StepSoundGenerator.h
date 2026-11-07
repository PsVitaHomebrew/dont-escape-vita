// Generated from StepSoundGenerator.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/StepSoundGenerator.cpp
#pragma once
#include "../game_types.h"

class StepSoundGenerator : public MonoBehaviour {
public:
  // ---- fields
  P<AudioSource> aS{};
  bool secStep{};
  bool useDoubleStepSound = true;
  float volumeMultip = 1.0f;
  static String NORMAL;
  static String DIRT;
  static String WOOD;
  static String METAL;
  static String ROAD;
  static String GRASS;
  static String HAY;
  static String RUBBER;
  static String DIRT_GLASS;
  static String FENCE;
  static String MOON;
  List<P<AudioClip>> stepsNormal = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsDirt = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsRoad = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsWood = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsMetal = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsGrass = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsHay = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsRubber = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsDirtGlass = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsFence = List<P<AudioClip>>::New();
  List<P<AudioClip>> stepsMoon = List<P<AudioClip>>::New();
  Array<P<Sprite>> dustNormal{};
  Array<P<Sprite>> dustDirt{};
  Array<P<Sprite>> dustRoad{};
  Array<P<Sprite>> dustWood{};
  Array<P<Sprite>> dustMetal{};
  Array<P<Sprite>> dustGrass{};
  Array<P<Sprite>> dustHay{};
  Array<P<Sprite>> dustRubber{};
  String selectedStepsType = S("normal");
  float volume = 0.15f;
  List<P<AudioClip>> currtenSteps{};
  // ---- constructors
  StepSoundGenerator() {}
  // ---- methods
  void Start();
  void Update();
  void setDust(Array<P<Sprite>> dust);
  void setStepType2(String type, AudioReverbPreset reverb);
  void setStepType(String type);
  void soundStep();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
