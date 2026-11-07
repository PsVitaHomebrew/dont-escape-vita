#include "../game_all.h"

void BaseOutside2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (PlayerController::pc->spawnName == S("Funeral"))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_emotional);
	}
	else if (!GameDataController::gd->getObjective(S("visited_barn")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	}
	else if (JukeboxMusic::jb->getCurrentMusic() == SoundsManagerController::sm->music_explore_2a)
	{
		JukeboxMusic::jb->changeMusic(nullptr, false);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	GameDataController::gd->setObjective(S("visited_baseOutside2"), true);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_flag, 1.0f);
	}
	else
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	}
	if (GameDataController::gd->getCurrentDay() != 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		spider1->set_enabled(true);
		spider2->set_enabled(true);
	}
	else
	{
		spider1->set_enabled(false);
		spider2->set_enabled(false);
	}
	graveBlock1->set_enabled(false);
	graveBlock2->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1)
	{
		graveBlock1->set_enabled(true);
	}
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1)
	{
		graveBlock2->set_enabled(true);
	}
	if (GameDataController::gd->getCurrentDay() != 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		bugs->set_enabled(true);
	}
	else
	{
		bugs->set_enabled(false);
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
	}
	else
	{
		snow->set_enabled(false);
	}
	ItemsManager::im->fixGroundItems(Vector2(175.0f, 35.0f), Vector2(8.0f, 5.0f));
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	ItemsManager::im->initGroundAndInv();
}

void BaseOutside2Start::Update()
{
}
