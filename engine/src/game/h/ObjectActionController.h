// Generated from ObjectActionController.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ObjectActionController.cpp
#pragma once
#include "../game_types.h"

class ObjectActionController : public MonoBehaviour {
public:
  using Type = ObjectActionController_Type;
  // ---- fields
  ObjectActionController_Type actionType{};
  P<ColliderManager> colliderManager{};
  String characterAnimationName{};
  bool useCurrentDirection{};
  bool animationFlip{};
  P<GameObject> actionMarker{};
  P<WalkController> walkControllerOAC{};
  bool teleport{};
  float range = 1.0f;
  P<TextFieldController> textfield{};
  P<CursorController> cursorCont{};
  Array<KeyValueString> dkvs{};
  String objectName{};
  P<AudioSource> thisAudioSource{};
  List<P<ItemInteraction>> interactions{};
  bool allowAllItems{};
  static int BOTTOM_TEXT_WIDTH;
  P<Item> usedItemRef{};
  P<ItemInteraction> usedItemInteraction{};
  String usedItem{};
  bool needUpdate{};
  bool alreadyMouseEntered{};
  int clicks{};
  String doubleClickCondition = String(u"");
  WalkController_Direction trans_dir = WalkController_Direction::S_;
  P<LocationManager> currentLocationManager{};
  float runTimeout{};
  int run{};
  // ---- constructors
  ObjectActionController() {}
  // ---- methods
  void Awake();
  void initTextField();
  void setCollider(int n);
  void initCursor();
  void OnMouseOver();
  void fakeMouseOver();
  void fakeMouseDown();
  void OnMouseEnter();
  void OnMouseExit();
  void OnMouseDown();
  void fakeClick();
  void Update();
  void OnEnable();
  void animationComplete();
  void updateAll();
  virtual void whatOnClick();
  virtual void whatOnClick0();
  virtual void updateState() = 0;
  virtual void clickAction0() = 0;
  virtual void clickAction() = 0;
  virtual void clickAction2() = 0;
  virtual void mouseOver();
  virtual void mouseOut();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
