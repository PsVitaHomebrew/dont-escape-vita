#include "../game_all.h"

void IntroMoonShuttleControl::Start()
{
}

void IntroMoonShuttleControl::Update()
{
}

void IntroMoonShuttleControl::enableBackDust()
{
	d1->started = true;
	d2->started = true;
}

void IntroMoonShuttleControl::enableBackDust2()
{
	d5->started = true;
	d6->started = true;
}

void IntroMoonShuttleControl::enablefrontDust()
{
	d3->started = true;
	d4->started = true;
}

void IntroMoonShuttleControl::disableBackDust()
{
	d1->started = false;
	d2->started = false;
}

void IntroMoonShuttleControl::disablefrontDust()
{
	d3->started = false;
}

void IntroMoonShuttleControl::startSound()
{
	aS->PlayOneShot(SoundsManagerController::sm->ship_drag);
}

void IntroMoonShuttleControl::startSound2()
{
	aS->PlayOneShot(SoundsManagerController::sm->ship_drag2);
}

void IntroMoonShuttleControl::soundBum()
{
	aS->PlayOneShot(SoundsManagerController::sm->heli_crash, 0.5f);
}

void IntroMoonShuttleControl::soundPisk()
{
	aS->PlayOneShot(SoundsManagerController::sm->pisk, 0.25f);
}
