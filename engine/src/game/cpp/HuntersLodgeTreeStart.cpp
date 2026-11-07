#include "../game_all.h"

void HuntersLodgeTreeStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.03f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 0.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::GRASS, AudioReverbPreset::Forest);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_4a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_forest, 0.9f);
}

void HuntersLodgeTreeStart::Update()
{
}
