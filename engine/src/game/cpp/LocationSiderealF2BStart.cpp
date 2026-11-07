#include "../game_all.h"

void LocationSiderealF2BStart::Start()
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
	GameDataController::gd->setObjective(S("visited_sidereal_f2b"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		p1a->set_enabled(false);
		p2a->set_enabled(false);
		p3a->set_enabled(false);
		p4a->set_enabled(false);
		p1b->set_enabled(true);
		p2b->set_enabled(true);
		p3b->set_enabled(true);
		p4b->set_enabled(true);
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 20.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.5f;
		PlayerController::wc->shadow->scaleFactor = 0.5f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
		PlayerController::wc->shadow->source = 120.0f;
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.75f);
	}
	else
	{
		p1a->set_enabled(true);
		p2a->set_enabled(true);
		p3a->set_enabled(true);
		p4a->set_enabled(true);
		p1b->set_enabled(false);
		p2b->set_enabled(false);
		p3b->set_enabled(false);
		p4b->set_enabled(false);
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 2;
		PlayerController::wc->shadow->skewFactor = 0.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->scaleFactor = 1.0f;
		PlayerController::wc->shadow->downwards = false;
		PlayerController::wc->shadow->source = 120.0f;
		PlayerController::wc->shadow->startAlpha = 0.5f;
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	}
}

void LocationSiderealF2BStart::Update()
{
	PlayerController::wc->shadow->scaleFactor = 1.0f * (Mathf::Abs(PlayerController::wc->currentXY.y - 35.0f) / 35.0f);
	if (PlayerController::wc->shadow->scaleFactor < 0.1f)
	{
		PlayerController::wc->shadow->scaleFactor = 0.1f;
	}
	if (PlayerController::wc->currentXY.y < 35.0f)
	{
		PlayerController::wc->shadow->downwards = true;
	}
	else
	{
		PlayerController::wc->shadow->downwards = false;
	}
}
