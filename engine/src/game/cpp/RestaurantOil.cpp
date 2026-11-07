#include "../game_all.h"

void RestaurantOil::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_oil");
	range = 2.0f;
	updateState();
}

void RestaurantOil::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_oil_taken")))
	{
		pickItUp(nullptr);
	}
}

void RestaurantOil::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("oil"))))
	{
		GameDataController::gd->setObjective(S("restaurant_oil_taken"), true);
		updateAll();
	}
}

void RestaurantOil::whatOnClick()
{
}

void RestaurantOil::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_chem_door_open")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else if (GameDataController::gd->getObjective(S("restaurant_oil_taken")))
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

void RestaurantOil::clickAction2()
{
}

void RestaurantOil::clickAction0()
{
}
