#include "../game_all.h"

void PesttruckSpiderPest3::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_truck_spider_pest3");
	updateState();
}

void PesttruckSpiderPest3::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest3"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_spiderpest3_taken"), true);
		updateState();
	}
}

void PesttruckSpiderPest3::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_spiderpest3_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
	{
		characterAnimationName = S("kneel_n");
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

void PesttruckSpiderPest3::clickAction2()
{
}

void PesttruckSpiderPest3::clickAction0()
{
}
