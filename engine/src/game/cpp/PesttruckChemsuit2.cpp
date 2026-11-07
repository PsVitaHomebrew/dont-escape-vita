#include "../game_all.h"

void PesttruckChemsuit2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("chemsuit");
	updateState();
}

void PesttruckChemsuit2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chemsuit"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_chemsuit_taken"), !GameDataController::gd->getObjective(S("pesttruck_chemsuit_taken")));
		updateState();
	}
}

void PesttruckChemsuit2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_chemsuit_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker2_open")))
	{
		characterAnimationName = S("action_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void PesttruckChemsuit2::clickAction2()
{
}

void PesttruckChemsuit2::clickAction0()
{
}
