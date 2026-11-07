// Generated from KongregateAPI.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/KongregateAPI.cpp
#pragma once
#include "../game_types.h"

class KongregateAPI : public MonoBehaviour {
public:
  // ---- fields
  static P<KongregateAPI> instance;
  unsigned gameId = 304604u;
  bool car_done{};
  bool disck_done{};
  bool game_done{};
  // ---- constructors
  KongregateAPI() {}
  // ---- methods
  void Awake();
  void Start();
  void UpdateEverySec();
  void OnDestroy();
  void HandleKongregateEvent(String name, String payload);
  void Log(String text);
  void submitBadge(String name);
  static void OnKongregateEvent(String name, String payload);
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
