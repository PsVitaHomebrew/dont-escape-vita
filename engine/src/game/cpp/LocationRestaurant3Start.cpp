#include "../game_all.h"

void LocationRestaurant3Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.02f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::NORMAL);
	PlayerController::wc->shadow->scaleFactor = 0.9f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_restaurant_inside"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_flag, 0.5f);
	GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->updateState();
	soliderStuff1->set_enabled(true);
	soliderStuff2->set_enabled(true);
	soliderStuff3->set_enabled(true);
	soliderStuff4->set_enabled(true);
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		if (!GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
		{
			GameDataController::gd->setObjective(S("restaurant_sarge_awaits"), false);
			solider1->set_enabled(true);
			solider2->set_enabled(true);
			solider4->set_enabled(true);
			solider1->gameObject->GetComponent<Animator>()->Play(S("solider1_aim_loop"));
			solider2->gameObject->GetComponent<Animator>()->Play(S("solider2_aim_loop"));
			solider4->gameObject->GetComponent<Animator>()->Play(S("solider4_aim"));
			solider1->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(solider1->gameObject->transform->get_position()));
			solider2->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(solider2->gameObject->transform->get_position()));
			solider4->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(solider4->gameObject->transform->get_position()));
			GameObject::Find(S("SargeObject"))->GetComponent<RestaurantSarge>()->initIntroDialogue();
			GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr"), true);
			if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setBusy(true);
			}
			if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr"), true);
			}
			Invoke(S("surr_npc"), 0.15f);
		}
		else
		{
			solider1->set_enabled(false);
			solider2->set_enabled(false);
			solider4->set_enabled(false);
			Invoke(S("antisurr_npc"), 0.15f);
		}
	}
	else
	{
		soliderStuff1->set_enabled(false);
		soliderStuff2->set_enabled(false);
		soliderStuff3->set_enabled(false);
		soliderStuff4->set_enabled(false);
		solider1->set_enabled(false);
		solider2->set_enabled(false);
		solider4->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("restaurant_door_opened")) && !GameDataController::gd->getObjective(S("dialogue_cody_door_opened")))
	{
		codySurprised = true;
	}
}

void LocationRestaurant3Start::surr_npc()
{
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr"), true);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr"), true);
	}
}

void LocationRestaurant3Start::antisurr_npc()
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setBusy(false);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setBusy(false);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setBusy(false);
	}
}

void LocationRestaurant3Start::Update()
{
	if (GameDataController::gd->getCurrentDay() != 2 || (!(PlayerController::wc->currentXY.x < 70.0f) && !(PlayerController::wc->currentXY.y > 15.0f)) || GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		return;
	}
	if (codySurprised)
	{
		codySurprised = false;
		GameDataController::gd->setObjective(S("restaurant_door_opened2"), true);
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised"), true);
		GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->fakeClick();
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		if (PlayerController::wc->currentXY.y > 15.0f)
		{
			PlayerController::wc->currentXY.y = 15.0f;
		}
		if (PlayerController::wc->currentXY.x < 70.0f)
		{
			PlayerController::wc->currentXY.x = 70.0f;
		}
		PlayerController::wc->fullStop(true);
		PlayerController::pc->clickedAlreadyForSomething = false;
		GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->fakeClick();
	}
}
