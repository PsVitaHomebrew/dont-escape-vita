// Generated from SteamManager.cs by tools/gen/gen.js - do not edit. Method bodies: src/game/cpp/SteamManager.cpp
#pragma once
#include "../game_types.h"

class SteamManager : public MonoBehaviour {
public:
  // ---- fields
  static P<SteamManager> s_instance;
  static bool s_EverInialized;
  bool m_bInitialized{};
  SteamAPIWarningMessageHook_t m_SteamAPIWarningMessageHook{};
  // ---- constructors
  SteamManager() {}
  // ---- properties
  static P<SteamManager> get_Instance();
  static bool get_Initialized();
  // ---- methods
  static void SteamAPIDebugTextHook(int nSeverity, StringBuilder pchDebugText);
  void Awake();
  void OnEnable();
  void OnDestroy();
  void Update();
  // ---- generated
  void _load(FieldReader& r) override;
  void _clearRefs() override;
  const ClassInfo* _getClassInfo() const override;
  void _saveSerialized(JsonWriter& w) override;
};
