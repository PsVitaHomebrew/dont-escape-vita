#include "../game_all.h"

void LocationSiderealF2SStart::Start()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 20.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.75f;
		PlayerController::wc->shadow->scaleFactor = 0.5f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
		PlayerController::wc->shadow->source = 120.0f;
		PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::StoneCorridor);
		GameDataController::gd->setObjective(S("visited_sidereal_f2s"), true);
		PlayerController::pc->copySettingsToNPCs();
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 0.5f);
		light->set_enabled(true);
		light2->set_enabled(true);
		shadows->set_enabled(true);
		pc_on->set_enabled(true);
		pc_off->set_enabled(false);
		dark->set_enabled(false);
	}
	else
	{
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 40.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.75f;
		PlayerController::wc->shadow->scaleFactor = 0.5f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
		PlayerController::wc->shadow->source = 230.0f;
		PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::StoneCorridor);
		PlayerController::pc->copySettingsToNPCs();
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
		light->set_enabled(false);
		light2->set_enabled(false);
		shadows->set_enabled(false);
		pc_on->set_enabled(false);
		pc_off->set_enabled(true);
		dark->set_enabled(true);
	}
}

void LocationSiderealF2SStart::Update()
{
}
