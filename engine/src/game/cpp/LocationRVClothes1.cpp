#include "../game_all.h"

void LocationRVClothes1::Start()
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

void LocationRVClothes1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("coat3"))))
	{
		GameDataController::gd->setObjective(S("rv_coat1_taken"), true);
		updateAll();
	}
}

void LocationRVClothes1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_coat1_taken")) || !GameDataController::gd->getObjective(S("rv_shelf2_open")))
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

void LocationRVClothes1::clickAction2()
{
}

void LocationRVClothes1::clickAction0()
{
}

void LocationRVClothes1::whatOnClick0()
{
}

void LocationRVClothes1::whatOnClick()
{
}
