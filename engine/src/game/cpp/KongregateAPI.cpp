#include "../game_all.h"

void KongregateAPI::Awake()
{
	if (instance != nullptr)
	{
		Object::Destroy(gameObject);
		return;
	}
	Object::DontDestroyOnLoad(gameObject);
	instance = this;
}

void KongregateAPI::Start()
{
	Debug::Log(S("Initializing KongregateAPI SDK"));
	InvokeRepeating(S("UpdateEverySec"), 1.0f, 1.0f);
}

void KongregateAPI::UpdateEverySec()
{
	bool flag = false;
	bool flag2 = false;
	if (flag && flag2 && GameDataController::gd != nullptr && GameDataController::persistentData != nullptr)
	{
		if (GameDataController::persistentData->kong_car && !car_done)
		{
			submitBadge(S("car_fixed"));
			car_done = true;
		}
		if (GameDataController::persistentData->kong_disk && !disck_done)
		{
			submitBadge(S("disk_taken"));
			disck_done = true;
		}
		if (GameDataController::persistentData->kong_game && !game_done)
		{
			submitBadge(S("game_won"));
			game_done = true;
		}
	}
}

void KongregateAPI::OnDestroy()
{
	Debug::Log(S("Shutting down the Kongregate API"));
}

void KongregateAPI::HandleKongregateEvent(String name, String payload)
{
	String text = S("[Event:") + name + S("] - ") + payload;
	Log(text);
	if (!(name == S("user")) && name == S("auth_token"))
	{
	}
}

void KongregateAPI::Log(String text)
{
	Debug::Log(text);
}

void KongregateAPI::submitBadge(String name)
{
	Log(S("Submitting badge: ") + name);
}

void KongregateAPI::OnKongregateEvent(String name, String payload)
{
	instance->HandleKongregateEvent(name, payload);
}
