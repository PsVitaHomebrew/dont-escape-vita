#include "../game_all.h"

void BaseOutside1Start::Start()
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
	GameObject::Find(S("Bike"))->GetComponent<LocationBaseOutside1Bike>()->updateAll();
	if (!GameDataController::gd->getObjective(S("visited_barn")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	}
	else if (GameDataController::gd->getCurrentDay() == 4 && !GameDataController::gd->getObjective(S("d4_intro")))
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_2a);
	}
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		moon->set_sprite(moon1);
	}
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		moon->set_sprite(moon2);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		moon->set_sprite(moon3);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		moon->set_sprite(moon4);
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		moong->set_sprite(moon1g);
	}
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		moong->set_sprite(moon2g);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		moong->set_sprite(moon3g);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		moong->set_sprite(moon4g);
	}
	if (GameDataController::gd->gameTime < 510 || GameDataController::gd->gameTime >= 1050)
	{
		moong->set_enabled(true);
	}
	else
	{
		moong->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		heli->set_enabled(false);
	}
	else
	{
		heli->set_enabled(true);
	}
	if (!GameDataController::gd->getObjective(S("visited_baseOutside1")))
	{
		Invoke(S("showIntro2"), 0.25f);
		Invoke(S("showIntro1b"), 8.0f);
	}
	GameDataController::gd->setObjective(S("visited_baseOutside1"), true);
	if (GameDataController::gd->getCurrentDay() == 4 && !GameDataController::gd->getObjective(S("d4_intro")))
	{
		d4Intro();
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
	if (GameDataController::gd->getObjective(S("helicopter_covered")))
	{
		coptercoat->set_enabled(true);
	}
	else
	{
		coptercoat->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		roof1->set_enabled(false);
		roof->set_enabled(true);
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

void BaseOutside1Start::showIntro2()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.x = 64.0f;
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->shift.y = -20.0f;
	if (!GameDataController::gd->getObjective(S("intro_skipped")))
	{
		GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("intro_4")), false, true, true, 180, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void BaseOutside1Start::showIntro1b()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(S(" "), false, true, true, 180, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void BaseOutside1Start::Update()
{
	if (runState != 0.0f)
	{
		if (runState == 1.0f && cody->currentXY.x > 120.0f)
		{
			runState = 2.0f;
			runLikeCrazy(String::Empty);
		}
		if (runState == 2.0f && cody->currentXY.x > 150.0f)
		{
			runState = 3.0f;
			runLikeCrazy(String::Empty);
		}
		if (runState == 3.0f && cody->currentXY.x < 95.0f)
		{
			runState = 1.0f;
			runLikeCrazy(String::Empty);
		}
	}
}

void BaseOutside1Start::d4Intro()
{
	GameDataController::gd->setObjective(S("d4_intro"), true);
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		if (GameDataController::gd->getObjective(S("thug_killed_bathroom")))
		{
			DialogueController::dc->initDialogue(list, S("day4_intro_talk_kill"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		}
		else
		{
			DialogueController::dc->initDialogue(list, S("day4_intro_talk_no_kill"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		}
	}
	DialogueController::dc->initDialogue(list, S("day4_intro_talk"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
	{
		Vector3 color = Npc2Controller::getColor();
		P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("day4_intro_talk_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor(), component2, color);
		if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")))
		{
			list[list.Count() - 1 - 5]->text = GameStrings::getString(GameStrings::dialogues, S("day4_intro_talk_barry_2_c_no_cody"));
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		Vector3 color2 = Npc3Controller::getColor();
		P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("day4_intro_talk_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor(), component3, color2);
		list[3]->action = [this](String s) { turnNorth(s); };
		list[list.Count() / 2]->action = [this](String s) { turnNorth2(s); };
		list[list.Count() - 1]->action = [this](String s) { runLikeCrazy(s); };
		list[list.Count() - 1]->actionWithText = true;
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void BaseOutside1Start::turnNorth2(String s)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setBusy(false);
}

void BaseOutside1Start::turnNorth(String s)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"));
}

void BaseOutside1Start::runLikeCrazy(String s)
{
	if (runState == 0.0f)
	{
		runState = 1.0f;
	}
	cody->speed = 4.0f;
	if (runState == 1.0f)
	{
		cody->setSimpleTargetV3(codyRun3->transform->get_position());
		cody->forceAnimation(S("cody_run"));
	}
	if (runState == 2.0f)
	{
		cody->setSimpleTargetV3(codyRun1->transform->get_position());
		cody->forceAnimation(S("cody_run"));
	}
	if (runState == 3.0f)
	{
		cody->setSimpleTargetV3(codyRun2->transform->get_position());
		cody->forceAnimation(S("cody_run"), true);
	}
}
