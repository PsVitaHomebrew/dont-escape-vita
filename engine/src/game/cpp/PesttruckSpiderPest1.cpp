#include "../game_all.h"

void PesttruckSpiderPest1::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_truck_spider_pest1");
	updateState();
}

void PesttruckSpiderPest1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spiderpest1"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_spiderpest1_taken"), true);
		updateState();
	}
}

void PesttruckSpiderPest1::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_spiderpest1_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
	{
		characterAnimationName = S("kneel_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else if (GameDataController::gd->getObjective(S("pesttruck_spiderpest1_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker1_open")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite2);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void PesttruckSpiderPest1::clickAction2()
{
}

void PesttruckSpiderPest1::clickAction0()
{
}
