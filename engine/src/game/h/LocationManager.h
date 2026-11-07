// Generated from LocationManager.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/LocationManager.cpp
#pragma once
#include "../game_types.h"

class LocationManager : public MonoBehaviour {
public:
  // ---- fields
  int pixelsW = 240;
  int pixelsH = 135;
  int nodesW = 48;
  int nodesH = 27;
  Array<P<Node>> nodes{};
  bool DEBUG{};
  LayerMask pathLayer{};
  LayerMask blockingLayer{};
  P<Node> startNode{};
  P<Node> endNode{};
  P<ClockController> cc{};
  P<ObjectActionController> esc{};
  P<Button> escButton{};
  P<Button> escButton2{};
  bool walkable = true;
  bool suit{};
  bool needSpecialCamera = true;
  P<GameObject> MainCamera{};
  P<Camera> MainCameraC{};
  P<GameObject> UICamera{};
  float needShake{};
  float aaa{};
  float factor{};
  bool showInventory = true;
  bool itemsHighlighted{};
  Vector3 cameraMoved{};
  Rect previousCameraRect{};
  float thunderDelay{};
  // ---- constructors
  LocationManager() {}
  // ---- methods
  void canPickUpItems();
  void cantPickupItems();
  void Start();
  void checkResolution();
  void needFix();
  void blinkMaybe();
  void Update();
  void highlightItems(bool show);
  void initNodes();
  void OnMouseOver();
  static float dist(Vector2 a, Vector2 b);
  bool Search(P<Node> currentNode);
  void resetShadow();
  Vector2 getNodeLocation(Vector2 sourceLocation);
  void setPathStart(Vector2 start);
  void setPathEnd(Vector2 end);
  Vector2 findNearestClearNode(Vector2 source);
  List<Vector2> GetAdjacentLocations(Vector2 location);
  List<P<Node>> GetAdjacentWalkableNodes(P<Node> fromNode);
  List<Vector2> FindPath(Vector2 start, Vector2 finish);
  List<Vector2> Search2(Vector2 start, Vector2 finish);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
