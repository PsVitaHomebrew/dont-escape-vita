#include "../game_all.h"

void Location2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.005f;
	PlayerController::wc->shadow->fadeRateH = 0.005f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 40.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 16.0f;
	PlayerController::ssg->setStepType(S("normal"));
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_location2"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	if (GameDataController::gd->getObjective(S("kitchen_oven_open")) && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		ko->lightAlfa = 1.0f;
		ko->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void Location2Start::Update()
{
}
