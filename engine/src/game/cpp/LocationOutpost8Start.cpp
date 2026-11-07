#include "../game_all.h"

void LocationOutpost8Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = -1;
	PlayerController::wc->shadow->skewFactor = 40.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.9f;
	PlayerController::wc->shadow->source = 60.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Hangar);
	PlayerController::wc->shadow->scaleFactor = 0.65f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_outpost8"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		sr1->set_enabled(true);
		sr2->set_enabled(true);
		sr3->set_enabled(true);
	}
	else
	{
		sr1->set_enabled(false);
		sr2->set_enabled(false);
		sr3->set_enabled(false);
	}
}

void LocationOutpost8Start::Update()
{
}
