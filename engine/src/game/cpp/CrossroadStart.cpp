#include "../game_all.h"

void CrossroadStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType(S("road"));
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	GameObject::Find(S("inventory_button"))->GetComponent<InventoryButtonController>()->showFinal();
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::pc->copySettingsToNPCs();
	if (!GameDataController::gd->getObjective(S("visited_crossroad")))
	{
		GameDataController::gd->autoSave();
		PlayerController::wc->currentXY.x = 100.0f;
		PlayerController::wc->currentXY.y = -70.0f;
		walkThere();
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		heli->set_enabled(false);
	}
	else
	{
		heli->set_enabled(true);
	}
	if (!GameDataController::gd->getObjective(S("visited_barn")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(nullptr, false);
	}
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	GameDataController::gd->setObjective(S("bridge_westside"), false);
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
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		roof->set_enabled(true);
	}
	ditches->set_enabled(false);
	if (GameDataController::gd->getObjective(S("base_outside_dug")))
	{
		ditches->set_enabled(true);
	}
}

void CrossroadStart::walkThere1()
{
	Invoke(S("walkThere"), 0.25f);
}

void CrossroadStart::walkThere()
{
	Invoke(S("showIntro1"), 1.0f);
	Invoke(S("showIntro1b"), 7.0f);
	PlayerController::wc->speed = 2.0f;
	PlayerController::wc->currentXY.x = 90.0f;
	PlayerController::wc->currentXY.y = -70.0f;
	Vector2 simpleTarget = Vector2(90.0f, 25.0f);
	PlayerController::wc->setSimpleTarget(simpleTarget);
	PlayerController::wc->forceAnimation(S("walk_n"));
}

void CrossroadStart::unlock()
{
	PlayerController::wc->fullStop();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimation(S("action_stnd_n"));
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crossroad_intro1")), true, false, false, 80);
}

void CrossroadStart::showIntro1()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.x = 64.0f;
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.y = -20.0f;
	if (!GameDataController::gd->getObjective(S("intro_skipped")))
	{
		GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("intro_3")), false, true, true, 180, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void CrossroadStart::showIntro2()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.x = 64.0f;
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.y = -20.0f;
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("intro_4")), false, true, true, 180, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void CrossroadStart::showIntro1b()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(S(" "), false, true, true, 180, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void CrossroadStart::Update()
{
	if (PlayerController::wc->currentXY.y > 22.0f && !GameDataController::gd->getObjective(S("visited_crossroad")))
	{
		GameDataController::gd->setObjective(S("visited_crossroad"), true);
		unlock();
	}
	if (!GameDataController::gd->getObjective(S("visited_crossroad")))
	{
		float num = 1.0f + (30.0f + PlayerController::wc->currentXY.y) / 30.0f;
		if (num < 0.0f)
		{
			num = 0.0f;
		}
		if (num > 1.0f)
		{
			num = 1.0f;
		}
		PlayerController::ssg->volumeMultip = num;
	}
	else
	{
		PlayerController::ssg->volumeMultip = 1.0f;
	}
}
