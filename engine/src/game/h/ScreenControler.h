// Generated from ScreenControler.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ScreenControler.cpp
#pragma once
#include "../game_types.h"

class ScreenControler : public Obj {
public:
  // ---- fields
  static int sourceWidth;
  static int sourceHeight;
  static float ratioWidth;
  static float ratioHeight;
  static float shiftRatioX;
  static float shiftRatioY;
  static float shiftX;
  static float shiftY;
  static Array<Vector2> allowedResolutions; // = new Vector2[11] { new Vector2(1920f, 1080f), new Vector2(1680f, 945f), new Vector2(1600f, 900f), new Vector2(1440f, 810f), new Vector2(1366f, 768f), new Vector2(1280f, 720f), new Vector2(1200f, 675f), new Vector2(1152f, 648f), new Vector2(1024f, 576f), new Vector2(960f, 540f), new Vector2(480f, 270f) }  (set in _cctor)
  static Array<Resolution> resolutions;
  // ---- constructors
  ScreenControler();
  // ---- methods
  static Vector2 getResolution();
  static Array<Resolution> getResolutions();
  static Vector2 getHighestResolution();
  static Vector2 getHighestWindowResolution();
  static void setFullScreenResolution();
  static void setWindowedResolution(int width);
  static void setSavedResolution();
  static float distance(Vector2 a, Vector2 b);
  static Vector2 getScale();
  static Vector2 gameToScreen(Vector2 vectorToChange);
  static Vector2 gameToScreen2(Vector2 vectorToChange);
  static Vector2 screenToGame(Vector2 vectorToChange);
  static Vector2 screenToGame2(Vector2 vectorToChange);
  static Vector3 roundToNearestFullPixelOld(Vector3 vectorToChange);
  static Vector3 roundToNearestFullPixel(Vector3 vectorToChange);
  static Vector3 roundToNearestFullPixel2(Vector3 vectorToChange);
  static Vector3 roundToNearestFullPixel3(Vector3 vectorToChange);
  // ---- generated
  static void _cctor(); // translator: set the static fields marked (set in _cctor)
  void _load(FieldReader& r);
  void _clearRefs();
  void _save(JsonWriter& w);
};
