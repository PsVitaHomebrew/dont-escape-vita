#include "../game_all.h"

P<SteamManager> SteamManager::get_Instance()
{
	if (s_instance == nullptr)
	{
		return New<GameObject>(S("SteamManager"))->AddComponent<SteamManager>();
	}
	return s_instance;
}

bool SteamManager::get_Initialized()
{
	return false;
}

void SteamManager::SteamAPIDebugTextHook(int nSeverity, StringBuilder pchDebugText)
{
	Debug::LogWarning(pchDebugText.ToString());
}

void SteamManager::Awake()
{
	if (s_instance != nullptr)
	{
		Object::Destroy(gameObject);
		return;
	}
	s_instance = P<SteamManager>(this);
	if (s_EverInialized)
	{
		throw Exception("Tried to Initialize the SteamAPI twice in one session!");
	}
	Object::DontDestroyOnLoad(gameObject);
	m_bInitialized = false;
}

void SteamManager::OnEnable()
{
	if (s_instance == nullptr)
	{
		s_instance = P<SteamManager>(this);
	}
}

void SteamManager::OnDestroy()
{
	if (!(s_instance != P<SteamManager>(this)))
	{
		s_instance = nullptr;
	}
}

void SteamManager::Update()
{
}
