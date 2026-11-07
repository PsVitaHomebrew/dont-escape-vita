#include "../game_all.h"

void LocationRestaurant1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -4;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 15.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::ROAD);
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_restaurant_front"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_flag, 1.0f);
	if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1 || !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		solider1->set_enabled(false);
		solider2->set_enabled(false);
	}
	else
	{
		solider1->set_enabled(true);
		solider2->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
		{
			solider1->gameObject->GetComponent<Animator>()->Play(S("solider1_aim_start"));
			solider2->gameObject->GetComponent<Animator>()->Play(S("solider2_aim_start"));
			GameDataController::gd->setObjective(S("gasstation_map_warned"), true);
			PlayerController::wc->forceAnimation(S("stand_ne"), true);
			GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setFlipped(true);
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			Vector3 color = GingerActionController::getColor();
			P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("soliders_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), s1->textField, RestaurantSolider1::color, s2->textField, RestaurantSolider2::color);
			DialogueController::dc->initDialogue(list, S("soliders_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), s1->textField, RestaurantSolider1::color, component, color);
			if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setFlipped(true);
				DialogueController::dc->initDialogue(list, S("soliders_intro1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
			}
			if (GameDataController::gd->getObjective(S("npc2_alive")))
			{
				GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setFlipped(true);
				DialogueController::dc->initDialogue(list, S("soliders_intro1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), s1->textField, RestaurantSolider1::color, GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
			}
			DialogueController::dc->initDialogue(list, S("soliders_intro3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), s1->textField, RestaurantSolider1::color, s2->textField, RestaurantSolider2::color);
			list[1]->action = [this](String s) { playerRotate(s); };
			list[2]->action = [this](String s) { npcSurr(s); };
			list[2]->actionWithText = true;
			list[5]->action = [this](String s) { playerSurr(s); };
			list[5]->actionWithText = true;
			list[7]->action = [this](String s) { cateSurr(s); };
			list[7]->actionWithText = true;
			list[list.Count() - 1]->action = [this](String s) { gotoRestaurant(s); };
			Timeline::t->doNotUnlock = true;
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
		}
		else
		{
			solider1->gameObject->GetComponent<Animator>()->Play(S("solider1_guard_loop"));
			solider2->gameObject->GetComponent<Animator>()->Play(S("solider2_guard_loop"));
		}
	}
	pylon->set_enabled(false);
	if (GameDataController::gd->getObjective(S("r_sarge_catcher")))
	{
		pylon->set_enabled(true);
	}
}

void LocationRestaurant1Start::playerRotate(String s)
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(true);
	PlayerController::wc->dir = WalkController::Direction::NW;
	PlayerController::wc->forceAnimation(S("stand_ne"), true);
	PlayerController::wc->dir = WalkController::Direction::NW;
}

void LocationRestaurant1Start::playerSurr(String s)
{
	PlayerController::wc->forceAnimation(S("surr_start"), true);
}

void LocationRestaurant1Start::npcSurr(String s)
{
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_start"), true);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_start"), true);
	}
}

void LocationRestaurant1Start::cateSurr(String s)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_start"), true);
}

void LocationRestaurant1Start::gotoRestaurant(String s)
{
	PlayerController::pc->spawnName = S("WaypointRestaurantArrest");
	CurtainController::cc->fadeOut(S("LocationRestaurant3"), WalkController::Direction::N, S("surr"), nullptr, true);
}

void LocationRestaurant1Start::Update()
{
}
