// Generated from TravelAgency.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/TravelAgency.cpp
#pragma once
#include "../game_types.h"
#include "ObjectActionController.h"

class TravelAgency : public ObjectActionController {
public:
  // ---- fields
  static int LOCATION_STATUS_UNDISCOVERED;
  static int LOCATION_STATUS_UNREACHABLE;
  static int LOCATION_STATUS_REACHABLE;
  P<MapXController> xMark{};
  P<MapOController> oMark{};
  String locationName{};
  bool hoverThis{};
  P<SpriteRenderer> sr{};
  List<P<TravelAgency>> nodes{};
  List<P<Sprite>> travelDots{};
  List<int> travelTimes{};
  Array<String> locations{};
  Array<String> spawns{};
  Array<WalkController_Direction> facing{};
  P<MapTextController> topText{};
  int calculatedTime{};
  int fuel{};
  P<SpriteRenderer> routeRenderer{};
  List<List<P<TravelAgency>>> routes{};
  List<P<TravelAgency>> fastestRoute{};
  String unlockingDataRefName{};
  P<FuelController> fc{};
  // ---- constructors
  TravelAgency() {}
  // ---- methods
  void Start();
  void renderRoute(P<Sprite> spr = nullptr, bool red = false);
  void travel(List<P<TravelAgency>> travelNodes);
  void addRoute(List<P<TravelAgency>> ta);
  void mouseOver() override;
  void mouseOut() override;
  void updateState() override;
  void changeLocationIcon(String a, String b);
  void revealThisLocation();
  void unlockGame();
  void iconOn();
  void iconOff();
  void iconGrayed();
  void whatOnClick0() override;
  bool isOnRoute(String name);
  void clickAction() override;
  void yesInvestigateGasStation();
  void yesInvestigateBus();
  void noDoNotInvestigateGasStation();
  void noDoNotInvestigateBus();
  void yesGoToSiderealOnFoot();
  void yesGoToBridgeInstead();
  void clickAction2() override;
  void clickAction0() override;
  bool canIGoThereByCar();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
