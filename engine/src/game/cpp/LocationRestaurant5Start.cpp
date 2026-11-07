#include "../game_all.h"

void LocationRestaurant5Start::Start()
{
	shadowbegone = false;
	PlayerController::wc->shadow->fadeRateV = 0.002f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 25.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType2(S("normal"), AudioReverbPreset::Stoneroom);
	GameDataController::gd->setObjective(S("visited_restaurant_wc"), true);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_flag, 0.25f);
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		block->set_enabled(false);
		if (GameDataController::gd->getObjective(S("restaurant_chem_door_open")))
		{
			block2->set_enabled(false);
		}
	}
	else
	{
		block->set_enabled(true);
		block2->set_enabled(true);
	}
	if (GameDataController::gd->getObjective(S("restaurant_chem_walked")))
	{
		al = 0.0f;
	}
	else
	{
		al = 1.0f;
	}
	shadow->set_color(Color(1.0f, 1.0f, 1.0f, al));
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationRestaurant5Start::Update()
{
	if (PlayerController::wc->currentXY.y < 40.0f && !GameDataController::gd->getObjective(S("restaurant_chem_walked")))
	{
		shadowbegone = true;
		GameDataController::gd->setObjective(S("restaurant_chem_walked"), true);
		GameObject::Find(S("Conspiracy"))->GetComponent<RestaurantConspiracy>()->updateState();
	}
	if (shadowbegone)
	{
		al -= Time::get_deltaTime();
		if (al < 0.0f)
		{
			al = 0.0f;
			shadowbegone = false;
		}
		shadow->set_color(Color(1.0f, 1.0f, 1.0f, al));
	}
}
