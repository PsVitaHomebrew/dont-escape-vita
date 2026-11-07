#include "../game_all.h"

void LocationMoonbase2Window::Start()
{
	if (GameDataController::gd->getObjective(S("moon_window_cracked")))
	{
		GetComponent<Animator>()->Play(S("window_cracked"));
	}
	else
	{
		GetComponent<Animator>()->Play(S("window_normal"));
	}
}

void LocationMoonbase2Window::Update()
{
}

void LocationMoonbase2Window::crack()
{
	GetComponent<Animator>()->Play(S("window_crack"));
}

void LocationMoonbase2Window::sound1()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->glass_crack_1);
}

void LocationMoonbase2Window::sound2()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->glass_crack_2);
}
