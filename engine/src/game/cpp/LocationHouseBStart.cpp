#include "../game_all.h"

void LocationHouseBStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 1.2f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::DIRT);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::ssg->setStepType(S("road"));
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_house_b"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_4a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		if (PlayerController::pc->spawnName.Equals(S("WaypointHouseB2")) || PlayerController::pc->spawnName.Equals(S("WaypointHouseB1")))
		{
			GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->distractBarryEnd();
		}
		else
		{
			GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->distractBarry();
		}
	}
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		snow->set_enabled(true);
		if (GameDataController::gd->gameTime < 600)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (GameDataController::gd->gameTime < 650)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.8f));
		}
		else if (GameDataController::gd->gameTime < 700)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.6f));
		}
		else if (GameDataController::gd->gameTime < 750)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.4f));
		}
		else if (GameDataController::gd->gameTime < 800)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.2f));
		}
		else
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.1f));
		}
		snow2->set_enabled(true);
		snow2->set_color(snow->get_color());
	}
	else
	{
		snow->set_enabled(false);
		snow2->set_enabled(false);
	}
}

void LocationHouseBStart::zalosne()
{
	GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->updateState();
}

void LocationHouseBStart::Update()
{
}
