#include "../game_all.h"

void LocationBridgeStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.031f;
	PlayerController::wc->shadow->fadeRateH = 0.005f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType(S("road"));
	GameDataController::gd->setObjective(S("visited_bridge"), true);
	if (GameDataController::gd->getObjectiveDetail(S("map_houseb_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
	{
		GameDataController::gd->setObjectiveDetail(S("map_houseb_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	if (GameDataController::gd->getObjectiveDetail(S("map_restaurant_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
	{
		GameDataController::gd->setObjectiveDetail(S("map_restaurant_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_1a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
}

void LocationBridgeStart::Update()
{
	if (PlayerController::wc->currentXY.x > 100.0f)
	{
		PlayerController::wc->shadow->source = 200.0f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
	}
	else
	{
		PlayerController::wc->shadow->source = 0.0f;
		PlayerController::wc->shadow->fadeRateH = 0.01f;
	}
}
