#include "../game_all.h"

void PesttruckSonic::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sonic");
}

void PesttruckSonic::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sonic"))))
		{
			GameDataController::gd->setObjective(S("pesttruck_sonic_taken"), !GameDataController::gd->getObjective(S("pesttruck_sonic_taken")));
			updateState();
		}
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sonic2"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_sonic_taken"), !GameDataController::gd->getObjective(S("pesttruck_sonic_taken")));
		updateState();
	}
}

void PesttruckSonic::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 0)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_sonic_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker4_open")))
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

void PesttruckSonic::clickAction2()
{
}

void PesttruckSonic::clickAction0()
{
}
