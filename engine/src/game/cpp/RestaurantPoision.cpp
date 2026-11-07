#include "../game_all.h"

void RestaurantPoision::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action1_e");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_poision");
	range = 2.0f;
	updateState();
}

void RestaurantPoision::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_poision_taken")))
	{
		pickItUp(nullptr);
	}
}

void RestaurantPoision::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("poison"))))
	{
		GameDataController::gd->setObjective(S("restaurant_poision_taken"), true);
		updateAll();
	}
}

void RestaurantPoision::whatOnClick()
{
}

void RestaurantPoision::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_chem_door_open")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else if (GameDataController::gd->getObjective(S("restaurant_poision_taken")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void RestaurantPoision::clickAction2()
{
}

void RestaurantPoision::clickAction0()
{
}
