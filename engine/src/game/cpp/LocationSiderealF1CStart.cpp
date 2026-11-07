#include "../game_all.h"

void LocationSiderealF1CStart::Start()
{
	PlayerController::wc->shadow->fadeRateH = 0.005f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) != 15 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) != 40)
	{
		red->set_enabled(false);
		red2->set_enabled(false);
		black->set_enabled(true);
		PlayerController::wc->shadow->source = 130.0f;
		PlayerController::wc->shadow->skewFactor = 40.0f;
		PlayerController::wc->shadow->fadeRateV = 0.01f;
		darkness->set_enabled(true);
	}
	else
	{
		red->set_enabled(true);
		red2->set_enabled(true);
		black->set_enabled(false);
		PlayerController::wc->shadow->source = 50.0f;
		PlayerController::wc->shadow->skewFactor = 30.0f;
		PlayerController::wc->shadow->fadeRateV = 0.001f;
		darkness->set_enabled(false);
	}
	GameDataController::gd->setObjective(S("visited_sidereal_f1c"), true);
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::StoneCorridor);
	PlayerController::pc->copySettingsToNPCs();
	if (!GameDataController::gd->getObjective(S("sidereal_barry_pipe_moved")))
	{
		pipeobs->set_enabled(true);
	}
	else
	{
		pipeobs->set_enabled(false);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
}

void LocationSiderealF1CStart::Update()
{
}
