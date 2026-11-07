#include "../game_all.h"

void BaseOutside0Start::Start()
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
	if (!GameDataController::gd->getObjective(S("visited_barn")))
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
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	GameDataController::gd->setObjective(S("visited_baseOutside0"), true);
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
	piorunochron->set_enabled(false);
	if (GameDataController::gd->getObjective(S("lighting_rod_installed")))
	{
		piorunochron->set_enabled(true);
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		piorunochron->set_enabled(false);
	}
}

void BaseOutside0Start::Update()
{
}
