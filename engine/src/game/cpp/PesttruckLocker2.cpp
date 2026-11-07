#include "../game_all.h"

void PesttruckLocker2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("open_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_locker");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("paperclip"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("key_lockers")), nullptr, String::Empty));
}

void PesttruckLocker2::clickAction()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker2_unlocked")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
		}
	}
	else if (usedItem == S("paperclip"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("pesttruck_locker")), QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, 15);
	}
	else if (usedItem != S("crowbar"))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_locked);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("pest_truck_locker_locked")), true);
		updateAll();
	}
}

void PesttruckLocker2::yesClicked()
{
	GameDataController::gd->setObjective(S("pesttruck_locker2_unlocked"), true);
	updateState();
	PlayerController::wc->dir = WalkController::Direction::N;
	CurtainController::cc->fadeOut();
}

void PesttruckLocker2::updateState()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker2_open")))
	{
		characterAnimationName = S("open_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(-1);
	}
	else
	{
		characterAnimationName = S("open_n");
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(0);
	}
}

void PesttruckLocker2::clickAction2()
{
	if (GameDataController::gd->getObjective(S("pesttruck_locker2_unlocked")))
	{
		GameDataController::gd->setObjective(S("pesttruck_locker2_open"), !GameDataController::gd->getObjective(S("pesttruck_locker2_open")));
		updateState();
		updateAll();
	}
	else if (usedItem == S("crowbar"))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->locker_01);
		GameDataController::gd->setObjective(S("pesttruck_locker2_unlocked"), true);
		GameDataController::gd->setObjective(S("pesttruck_locker2_open"), true);
		updateAll();
	}
}

void PesttruckLocker2::whatOnClick0()
{
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	if (usedItem == S("paperclip"))
	{
		if (GameDataController::gd->getObjective(S("pesttruck_locker2_unlocked")))
		{
			characterAnimationName = S("action_stnd_n");
		}
		else
		{
			characterAnimationName = S("action_stnd_n");
		}
	}
	else if (GameDataController::gd->getObjective(S("pesttruck_locker2_unlocked")))
	{
		characterAnimationName = S("open_n");
	}
	else if (usedItem == S("crowbar"))
	{
		characterAnimationName = S("crowbar_e");
		actionMarker = gameObject->transform->Find(S("Action_Marker2"))->gameObject;
	}
	else
	{
		characterAnimationName = S("locked_n");
	}
}

void PesttruckLocker2::clickAction0()
{
}
