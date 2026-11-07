#include "../game_all.h"

void LocationOutpost10Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.006f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 20.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Hallway);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_outpost10"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
}

void LocationOutpost10Start::Update()
{
	if (PlayerController::wc->currentXY.x > 120.0f)
	{
		PlayerController::wc->shadow->source = 200.0f;
	}
	else
	{
		PlayerController::wc->shadow->source = 40.0f;
	}
	PlayerController::wc->shadow->scaleFactor = 0.1f + Mathf::Abs(PlayerController::wc->currentXY.y - 25.0f) / 60.0f;
	if (PlayerController::wc->currentXY.y > 25.0f)
	{
		PlayerController::wc->shadow->downwards = false;
	}
	else
	{
		PlayerController::wc->shadow->downwards = true;
	}
	PlayerController::pc->copySettingsToNPCs();
}
