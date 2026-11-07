#include "../game_all.h"

void PesttruckBearTraps::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pesttruck_bear_traps");
	updateState();
}

void PesttruckBearTraps::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("pesttruck_bear_traps_taken")) == 0)
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bear_trap_1"))))
		{
			GameDataController::gd->setObjectiveDetail(S("pesttruck_bear_traps_taken"), 1);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("pesttruck_bear_traps_taken")) == 1 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bear_trap_2"))))
	{
		GameDataController::gd->setObjectiveDetail(S("pesttruck_bear_traps_taken"), 2);
	}
	updateAll();
}

void PesttruckBearTraps::whatOnClick()
{
}

void PesttruckBearTraps::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("pesttruck_bear_traps_taken")) == 0)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
		objectName = S("pesttruck_bear_traps");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("pesttruck_bear_traps_taken")) == 1)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite2);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
		objectName = S("pesttruck_bear_trap");
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
}

void PesttruckBearTraps::clickAction2()
{
}

void PesttruckBearTraps::clickAction0()
{
}
