#include "../game_all.h"

void RestaurantKnife::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_knife");
	range = 1.0f;
}

void RestaurantKnife::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_knife_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("knife"))))
	{
		GameDataController::gd->setObjective(S("restaurant_knife_taken"), true);
		updateState();
	}
}

void RestaurantKnife::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_knife_taken")) || !GameDataController::gd->getObjective(S("restaurant_cupboard3_open")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void RestaurantKnife::clickAction2()
{
}

void RestaurantKnife::clickAction0()
{
}
