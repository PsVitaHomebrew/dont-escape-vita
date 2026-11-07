#include "../game_all.h"

void PesttruckGlass::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("chem_glass");
	updateState();
}

void PesttruckGlass::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("chem_glass"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_chem_glass_taken"), !GameDataController::gd->getObjective(S("pesttruck_chem_glass_taken")));
		updateState();
	}
}

void PesttruckGlass::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1)
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("pesttruck_chem_glass_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker4_open")))
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

void PesttruckGlass::clickAction2()
{
}

void PesttruckGlass::clickAction0()
{
}
