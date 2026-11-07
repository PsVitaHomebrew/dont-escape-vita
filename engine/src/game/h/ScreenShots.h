// Generated from ScreenShots.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ScreenShots.cpp
#pragma once
#include "../game_types.h"

class ScreenShots : public MonoBehaviour {
public:
  // ---- fields
  int bigWidth = 90;
  int bigHeight = 51;
  int smallWidth = 36;
  int smallHeight = 20;
  bool takeShot{};
  String takeShotNOW = String(u"");
  P<Camera> camera{};
  static P<ScreenShots> ss;
  Array<uint8_t> small{};
  Array<uint8_t> big{};
  // ---- constructors
  ScreenShots() {}
  // ---- methods
  static String ScreenShotName(int width, int height);
  void Awake();
  void Start();
  P<Sprite> getSprite(String name, bool big = false);
  void shot();
  void shotAndSave(String path);
  void saveShots(String name);
  void LateUpdate();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
