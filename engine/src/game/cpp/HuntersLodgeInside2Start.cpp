#include "../game_all.h"

void HuntersLodgeInside2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.04f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 30.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.6f;
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::WOOD, AudioReverbPreset::Livingroom);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_4a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_forest, 0.5f);
	GameDataController::gd->setObjective(S("visited_hunters_lodge_2"), true);
}

void HuntersLodgeInside2Start::Update()
{
	if (PlayerController::wc->currentXY.x > 120.0f)
	{
		PlayerController::wc->shadow->skewFactor = 30.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->source = 160.0f;
	}
	else
	{
		PlayerController::wc->shadow->skewFactor = 0.0f;
		PlayerController::wc->shadow->skewFactor2 = -30.0f;
		PlayerController::wc->shadow->source = -10.0f;
	}
}
