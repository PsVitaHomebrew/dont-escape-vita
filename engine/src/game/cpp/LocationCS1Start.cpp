#include "../game_all.h"

void LocationCS1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 25.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal, 1.0f);
	GameDataController::gd->setObjective(S("visited_cs_1"), true);
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		guards->set_enabled(true);
		GameDataController::gd->setObjective(S("cs_safe"), false);
	}
	else
	{
		GameDataController::gd->setObjective(S("cs_safe"), true);
		guards->set_enabled(false);
	}
}

void LocationCS1Start::Update()
{
}
