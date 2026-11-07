#include "../game_all.h"

void LocationOutpost6Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.006f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 20.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Hallway);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("outpost_spaceship_discovered"), true);
	GameDataController::gd->setObjective(S("visited_outpost6"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
}

void LocationOutpost6Start::Update()
{
	if (PlayerController::wc->currentXY.x < 80.0f)
	{
		grate->set_enabled(true);
	}
	else
	{
		grate->set_enabled(false);
	}
}
