#include "../game_all.h"

void PesttruckDuct::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_ducttape");
}

void PesttruckDuct::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ducttape"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_ducttape_taken"), true);
		updateState();
	}
}

void PesttruckDuct::updateState()
{
	if (!GameDataController::gd->getObjective(S("pesttruck_ducttape_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker2_open")))
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

void PesttruckDuct::clickAction2()
{
}

void PesttruckDuct::clickAction0()
{
}
