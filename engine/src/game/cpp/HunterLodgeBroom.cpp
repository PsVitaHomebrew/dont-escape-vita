#include "../game_all.h"

void HunterLodgeBroom::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action1_e");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("broom");
}

void HunterLodgeBroom::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("broom"))))
	{
		GameDataController::gd->setObjective(S("lodge_broom_taken"), true);
		updateAll();
	}
}

void HunterLodgeBroom::updateState()
{
	if (!GameDataController::gd->getObjective(S("lodge_broom_taken")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
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

void HunterLodgeBroom::clickAction2()
{
}

void HunterLodgeBroom::clickAction0()
{
}
