#include "../game_all.h"

void Waypoint_Crashsite2_Pesttruck::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_truck_locked");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("paperclip"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("pest_truck_locked_pipe")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("key_pesttruck")), nullptr, String::Empty));
	trans_dir = WalkController::Direction::E;
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
		{
			objectName = S("pest_truck");
		}
		else
		{
			objectName = S("pest_truck_locked");
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
		{
			objectName = S("gas_truck");
		}
		else
		{
			objectName = S("gas_truck_locked");
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
		{
			objectName = S("pest_truck");
		}
		else
		{
			objectName = S("pest_truck_locked");
		}
	}
}

void Waypoint_Crashsite2_Pesttruck::clickAction()
{
	PlayerController::wc->forceDirection(WalkController::Direction::E);
	if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Pesttruck_Crashsite2");
		CurtainController::cc->fadeOut(S("LocationPesttruck"), WalkController::Direction::E);
	}
	else if (usedItem == S("crowbar"))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->crowbar_pry_open);
	}
	else if (usedItem == S("paperclip"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("pesttruck_locker")), QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, 15);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("pest_truck_locked")), true);
	}
}

void Waypoint_Crashsite2_Pesttruck::updateState()
{
	if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		actionType = Type::Transition;
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker2"))->gameObject;
		actionType = Type::NormalAction;
	}
	if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		interactions = List<P<ItemInteraction>>::New();
		gameObject->GetComponent<Animator>()->Play(S("crashsitetruckdoor_opened"), 0);
		colliderManager->setCollider(0);
		return;
	}
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("paperclip"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("pest_truck_locked_pipe")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("key_pesttruck")), nullptr, String::Empty));
	gameObject->GetComponent<Animator>()->Play(S("crashsitetruckdoor_closed"), 0);
	colliderManager->setCollider(0);
}

void Waypoint_Crashsite2_Pesttruck::clickAction2()
{
	if (GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->spawnName = S("Waypoint_Pesttruck_Crashsite2");
			CurtainController::cc->fadeOut(S("LocationPesttruck"), WalkController::Direction::E);
		}
	}
	else if (usedItem == S("crowbar"))
	{
		GameDataController::gd->setObjective(S("pesttruck_unlocked"), true);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<Animator>()->Play(S("crashsitetruckdoor_open"), 0);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("pest_truck_locked")), true);
	}
}

void Waypoint_Crashsite2_Pesttruck::whatOnClick()
{
	if (!GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker2"))->gameObject;
		doubleClickCondition = String::Empty;
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		doubleClickCondition = S("visited_pestTruck");
	}
	if (usedItem == S("crowbar"))
	{
		if (!GameDataController::gd->getObjective(S("pesttruck_unlocked")))
		{
			characterAnimationName = S("crowbar_e");
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("action_stnd_");
			useCurrentDirection = true;
		}
	}
	else if (usedItem == S("paperclip"))
	{
		characterAnimationName = S("stop");
		useCurrentDirection = true;
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_unlocked")))
	{
		characterAnimationName = S("action_stnd_e");
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = String::Empty;
		useCurrentDirection = false;
	}
}

void Waypoint_Crashsite2_Pesttruck::yesClicked()
{
	GameDataController::gd->setObjective(S("pesttruck_unlocked"), true);
	PlayerController::wc->forceDirection(WalkController::Direction::E);
	CurtainController::cc->fadeOut();
}

void Waypoint_Crashsite2_Pesttruck::clickAction0()
{
}
