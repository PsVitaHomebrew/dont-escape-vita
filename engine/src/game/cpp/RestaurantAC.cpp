#include "../game_all.h"

void RestaurantAC::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_s");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_ac");
	range = 2.0f;
	updateState();
}

void RestaurantAC::clickAction()
{
	pickItUp(nullptr);
}

void RestaurantAC::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ac"))))
	{
		GameDataController::gd->setObjective(S("restaurant_ac_taken"), true);
		updateState();
	}
}

void RestaurantAC::whatOnClick()
{
}

void RestaurantAC::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) != 0 || GameDataController::gd->getObjective(S("restaurant_ac_taken")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void RestaurantAC::clickAction2()
{
}

void RestaurantAC::clickAction0()
{
}
