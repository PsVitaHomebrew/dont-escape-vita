// Generated from TextFieldController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TextFieldController.cpp
#pragma once
#include "../game_types.h"

class TextFieldController : public MonoBehaviour {
public:
  // ---- fields
  Array<P<Sprite>> sprites{};
  List<String> spritesNames{};
  List<P<GameObject>> chars{};
  bool center{};
  int maxWidth{};
  float directionY = -1.0f;
  float smod = 0.08f;
  int pmod{};
  int pmod2{};
  bool isSmooth{};
  Vector2 shift = Vector2(0.0f, 18.0f);
  float waitTillDelete{};
  float currentWait{};
  bool keepAlive{};
  int lineHeight = 8;
  List<int> linesBegins{};
  List<int> linesLengths{};
  P<GameObject> black{};
  int longestLine{};
  String typed{};
  String queued{};
  bool positionEverytime{};
  bool blockTop = true;
  int OPTIONAL_MARGIN{};
  float delay{};
  float currentDelay{};
  int perUpdate{};
  float red = 1.0f;
  float green = 1.0f;
  float blue = 1.0f;
  float alpha = 1.0f;
  float bgred{};
  float bggreen{};
  float bgblue{};
  float bgalpha{};
  Array<uint8_t> bytes{};
  Vector2 norm1{};
  Vector3 norm2{};
  P<GameObject> container{};
  bool blockGame{};
  float currentHeight{};
  float zzz = -6.0f;
  int maxLines = -1;
  P<MonoBehaviour> test{};
  String remains{};
  P<AudioClip> pyk{};
  P<GameObject> MainCamera{};
  static float cameraShiftY;
  static float BASE_DELAY;
  bool force_pixel_font{};
  bool force_smooth_font{};
  bool useSeparateCamera = true;
  // ---- constructors
  TextFieldController() {}
  // ---- properties
  String get_TypedText();
  // ---- methods
  List<P<GameObject>> getChars();
  void createBlack();
  void setTime(float t);
  void Awake();
  void initThings();
  void updateFont();
  void positionTextfield(int x, int y);
  void setAlpha(float a);
  void setTextColor(float r, float g, float b);
  void setBGColor(float r, float g, float b, float a);
  void viewText(String text, bool blockG = false, bool quick = false, bool instant = false, int mwidth = -1, float r = 1.0f, float g = 1.0f, float b = 1.0f, float br = 0.0f, float bg = 0.0f, float bb = 0.0f, float ba = 0.75f, bool constantRefresh = false, bool mute = false);
  Vector3 coords(Vector2 source);
  void Update();
  void speedUp();
  void terminate();
  bool dissmiss(bool hard = false);
  void addText(String text);
  String ToHex(Array<uint8_t> bytes);
  void arrange();
  bool newLine(int num, int extraChars = 0);
  void positionCharacter(P<GameObject> ch, int lx);
  void placeAndCenterLine(int start, int end, int lineLength, int line);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
