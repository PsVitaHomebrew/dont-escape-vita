#include "../game_all.h"

void LocationRestaurant4Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0035f;
	PlayerController::wc->shadowOffsetY = -4;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -15.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->source = 0.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::NORMAL);
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_restaurant_inside"), true);
	GameDataController::gd->setObjective(S("visited_restaurant_kitchen"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_flag, 0.25f);
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) != 1)
	{
		ItemsManager::im->getItem(S("gasheater_empty"))->dataRef->droppedLocation = S("nowhere");
		ItemsManager::im->removeGroundItem(S("gasheater_empty"));
	}
}

void LocationRestaurant4Start::Update()
{
}
