#include "../game_all.h"

void PesttruckPest2::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_can");
	updateState();
}

void PesttruckPest2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pest2"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_pest2_taken"), !GameDataController::gd->getObjective(S("pesttruck_pest2_taken")));
		updateState();
	}
}

void PesttruckPest2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 0)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_pest2_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker2_open")))
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

void PesttruckPest2::clickAction2()
{
}

void PesttruckPest2::clickAction0()
{
}
