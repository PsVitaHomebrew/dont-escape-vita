#include "../game_all.h"

void LocationRVClothes2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_clothes");
	range = 1.0f;
}

void LocationRVClothes2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("coat4"))))
	{
		GameDataController::gd->setObjective(S("rv_coat2_taken"), true);
		updateAll();
	}
}

void LocationRVClothes2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_coat2_taken")) || !GameDataController::gd->getObjective(S("rv_shelf2_open")))
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationRVClothes2::clickAction2()
{
}

void LocationRVClothes2::clickAction0()
{
}

void LocationRVClothes2::whatOnClick0()
{
}

void LocationRVClothes2::whatOnClick()
{
}
