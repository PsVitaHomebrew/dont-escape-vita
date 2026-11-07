#include "../game_all.h"

void LocationOutpostShip2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = -1;
	PlayerController::wc->shadow->skewFactor = 100.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.4f;
	PlayerController::wc->shadow->source = 120.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Bathroom);
	PlayerController::wc->shadow->scaleFactor = 0.6f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_ship2"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	PlayerController::pc->allowDrop = false;
}

void LocationOutpostShip2Start::Update()
{
}
