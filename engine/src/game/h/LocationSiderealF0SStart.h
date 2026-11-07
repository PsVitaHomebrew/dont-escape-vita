// Generated from LocationSiderealF0SStart.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationSiderealF0SStart.cpp
#pragma once
#include "../game_types.h"

class LocationSiderealF0SStart : public MonoBehaviour {
public:
  // ---- fields
  P<ParticleGenerator> pg{};
  P<AudioSource> audio{};
  P<NPCWalkController> ginger{};
  P<NPCWalkController> cody{};
  P<NPCWalkController> barry{};
  P<GameObject> npc{};
  P<GameObject> npcTarget{};
  P<TextFieldController> npcTextField{};
  float txtAlpha = 1.0f;
  // ---- constructors
  LocationSiderealF0SStart() {}
  // ---- methods
  void Start();
  void sypnij();
  void dosc();
  void Update();
  void mourn(String s = S(""));
  void music(String s = S(""));
  void txtColor(String s = S(""));
  void walkDown(String s = S(""));
  void die(String s = S(""));
  void die2();
  void walkNPC(String s = S(""));
  void shadowNPC(P<NPCWalkController> npcWC);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
