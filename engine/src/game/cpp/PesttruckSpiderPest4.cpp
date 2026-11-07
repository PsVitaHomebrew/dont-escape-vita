#include "../game_all.h"

void PesttruckSpiderPest4::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_truck_spider_pest4");
	updateState();
}

void PesttruckSpiderPest4::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest4"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_spiderpest4_taken"), true);
		updateState();
	}
}

void PesttruckSpiderPest4::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_spiderpest4_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
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

void PesttruckSpiderPest4::clickAction2()
{
}

void PesttruckSpiderPest4::clickAction0()
{
}
