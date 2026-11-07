#include "../game_all.h"

void OutpostRadarBeep::Start()
{
	radar = SoundsManagerController::sm->radarbeep;
	aS = GetComponent<AudioSource>();
}

void OutpostRadarBeep::beep()
{
	aS->PlayOneShot(radar);
}

void OutpostRadarBeep::Update()
{
}
