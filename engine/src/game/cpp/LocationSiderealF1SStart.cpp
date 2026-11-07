#include "../game_all.h"

void LocationSiderealF1SStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.005f;
	PlayerController::wc->shadow->fadeRateH = 0.005f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 1.0f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 120.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::StoneCorridor);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_sidereal_f1s"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
}

void LocationSiderealF1SStart::Update()
{
}
