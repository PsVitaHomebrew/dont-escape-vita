#include "../game_all.h"

void LocationSiderealOutside2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	GameDataController::gd->setObjective(S("visited_sidereal_outside_2"), true);
	if (GameDataController::gd->getObjective(S("barry_warned")))
	{
		GameDataController::gd->setObjective(S("npc2_joined"), true);
	}
	if (GameDataController::gd->getObjective(S("cody_warned")))
	{
		GameDataController::gd->setObjective(S("npc3_joined"), true);
	}
}

void LocationSiderealOutside2Start::Update()
{
}
