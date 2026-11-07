#include "../game_all.h"

void Gasstation2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.12f;
	PlayerController::wc->shadow->fadeRateH = 0.001f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType(S("road"));
	GameDataController::gd->setObjective(S("visited_gasstation2"), true);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getCurrentDay() == 1 && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a, true, 1.0f, 3.0f);
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && !GameDataController::gd->getObjective(S("gasstation_sarge_reason")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	}
	starter();
	updateDontKillCPUplz = false;
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && !GameDataController::gd->getObjective(S("gasstation_spy_mode")) && !GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		updateDontKillCPUplz = true;
	}
}

void Gasstation2Start::starter()
{
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("thugs_gasstation_talk")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("gasstation_thugs"), sarge, sargeColor, thug, thugColor, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc3_joined")))
		{
			list[5]->text = GameStrings::getString(GameStrings::dialogues, S("gasstation_thugs_6_b_cody_barry"));
		}
		else if (GameDataController::gd->getObjective(S("npc2_joined")))
		{
			list[5]->text = GameStrings::getString(GameStrings::dialogues, S("gasstation_thugs_6_b_barry"));
		}
		else if (GameDataController::gd->getObjective(S("npc3_joined")))
		{
			list[5]->text = GameStrings::getString(GameStrings::dialogues, S("gasstation_thugs_6_b_cody"));
		}
		list[18]->action = [this](String param) { thug2Go(param); };
		list[18]->actionWithText = true;
		list[19]->action = [this](String param) { sargeKneel(param); };
		list[19]->actionWithText = false;
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		GameDataController::gd->setObjective(S("thugs_gasstation_talk"), true);
		GameDataController::gd->setObjectiveDetail(S("map_construction_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
		ItemsManager::im->fixGroundItems(Vector2(175.0f, 35.0f), Vector2(5.0f, 2.0f));
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		ItemsManager::im->initGroundAndInv();
		bike->set_enabled(true);
		bikeBlock->set_enabled(true);
		sargeBlock->set_enabled(true);
		thug2Controller->GetComponent<SpriteRenderer>()->set_enabled(true);
		thug3Controller->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		ItemsManager::im->fixGroundItems(Vector2(175.0f, 35.0f), Vector2(5.0f, 2.0f));
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		ItemsManager::im->initGroundAndInv();
		bike->set_enabled(true);
		bikeBlock->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("gasstation_sarge_shot")) && !GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
		{
			sargeBlock->set_enabled(true);
		}
		else
		{
			sargeBlock->set_enabled(false);
		}
		if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
		{
			bike->set_enabled(false);
			bikeBlock->set_enabled(false);
			sargeBlock->set_enabled(false);
		}
		thug2Controller->GetComponent<SpriteRenderer>()->set_enabled(false);
		thug3Controller->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		bike->set_enabled(false);
		bikeBlock->set_enabled(false);
		sargeBlock->set_enabled(false);
		thug2Controller->GetComponent<SpriteRenderer>()->set_enabled(false);
		thug3Controller->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("SpyWalkArea"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		PlayerController::pc->allowDrop = false;
	}
	else
	{
		PlayerController::pc->allowDrop = true;
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("SpyWalkArea"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && !GameDataController::gd->getObjective(S("gasstation_spy_mode")) && !GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			PlayerController::pc->setBusy(true);
			PlayerController::pc->forceAnimation(S("walk_e"));
			Invoke(S("forceTalk0"), 0.01f);
			forceTalk1();
		}
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			snowr->set_enabled(true);
		}
		else
		{
			snowr->set_enabled(false);
		}
	}
	else
	{
		snowr->set_enabled(false);
	}
}

void Gasstation2Start::thug2Go(String param)
{
	thug2Controller->ride();
	thug3Controller->ride();
}

void Gasstation2Start::forceTalk0()
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->setSimpleTarget(ScreenControler::roundToNearestFullPixel(GameObject::Find(S("WalkToGun"))->transform->get_position()));
}

void Gasstation2Start::forceTalk1()
{
	GameObject::Find(S("sargeObject"))->GetComponent<GasstationSargeObject>()->initIntroDialogue();
}

void Gasstation2Start::sargeKneel(String param)
{
	sargeController->kneel();
}

void Gasstation2Start::Update()
{
	if (updateDontKillCPUplz && PlayerController::wc->currentXY.x >= ScreenControler::roundToNearestFullPixel(GameObject::Find(S("WalkToGun"))->transform->get_position()).x)
	{
		updateDontKillCPUplz = false;
		PlayerController::wc->forceAnimation(S("stand_se"));
	}
}
