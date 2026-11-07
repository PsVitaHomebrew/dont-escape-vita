// Generated from ItemsManager.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/ItemsManager.cpp
#pragma once
#include "../game_types.h"

class ItemsManager : public MonoBehaviour {
public:
  // ---- fields
  static P<ItemsManager> im;
  P<GameObject> inv{};
  List<P<Item>> items{};
  // ---- constructors
  ItemsManager() {}
  // ---- methods
  void Awake();
  void reloadAfterLanguageChange();
  void Start();
  void scary();
  void power_gluegon();
  void combineItems(String item1, String item2, String result);
  void resetSpring1();
  void open_remote();
  void break_remote();
  void resetSpring2();
  void resetSpring1b();
  void resetSpring1c();
  void resetSpring2b();
  void resetSpring2c();
  void rifleInstallScope();
  void rifleInstallScope2();
  void putAwayOrDropIfTheResultIsTooHeavy(String theThing);
  void rifleInstallSilencer();
  void rifleInstallSilencer2();
  void siderealIdExamined();
  void activate_absorber(String subject);
  void activate_absorber_ground(String subject);
  void activate_absorber_1();
  void activate_absorber_1_ground();
  void activate_absorber_2();
  void activate_absorber_2_ground();
  void activate_absorber_3();
  void activate_absorber_3_ground();
  void put_tank_heater();
  void put_tank_heater_ground();
  void locketRead();
  void rope_hook_use();
  void sonic_remote_use();
  void sledgehammer_fix1();
  void sledgehammer_fix2();
  void sledgehammer_fix3(String it2);
  void fan_fix1();
  void fan_fix2();
  void heater_fix1();
  void heater_fix2();
  void hammer_fix();
  void can_open();
  void reloadGun();
  void reloadRifle();
  void can_open_knife();
  void can_open_screwdriver();
  void chemsuit_fix1();
  void chemsuit_fix2();
  void chemsuit_filter1();
  void chemsuit_filter2();
  void fuel_generator();
  void fuel_sprayer_use();
  void fuel_sprayer_use2();
  void lighter_sprayer_use();
  void revolverShot(String gunName);
  void rifleShot(String gunName, bool boom = true);
  void OnEnable();
  void removeGroundItem(String itemName);
  void initGroundAndInv();
  void fixGroundItems(Vector2 newLoc, Vector2 shift);
  void updateItem(String id, String droppedLocation, int locX, int locY);
  void initItem(String name, float weight, String soundName, List<P<ItemInteraction>> usablesI = nullptr, List<P<ItemInteraction>> usablesG = nullptr, int animationFrames = 0, int animationDelay = 0, bool hasExamineScreen = false, int var1 = 0, int var2 = 0, int var3 = 0, int var4 = 0, List<String> texts = nullptr, int wid = 120, int xShift = 0, int yShift = 0, float r1 = 0.0f, float g1 = 0.0f, float b1 = 0.0f, float a1 = 1.0f, float r2 = 1.0f, float g2 = 1.0f, float b2 = 1.0f, float a2 = 1.0f, bool cycle = false, ExamineSprite_Delegate lookAction = nullptr, String soundL = S(""), bool actionOnLook = true);
  void initItems();
  static void exmineItem(P<Item> itemRef);
  P<Item> getItem(String name);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
