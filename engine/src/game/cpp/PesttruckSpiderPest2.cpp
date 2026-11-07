#include "../game_all.h"

void PesttruckSpiderPest2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_truck_spider_pest2");
	updateState();
}

void PesttruckSpiderPest2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest2"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_spiderpest2_taken"), true);
		updateState();
	}
}

void PesttruckSpiderPest2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_spiderpest2_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
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

void PesttruckSpiderPest2::clickAction2()
{
}

void PesttruckSpiderPest2::clickAction0()
{
}
