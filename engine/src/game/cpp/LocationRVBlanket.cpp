#include "../game_all.h"

void LocationRVBlanket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_blanket");
	range = 1.0f;
}

void LocationRVBlanket::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("blanket"))))
	{
		GameDataController::gd->setObjective(S("rv_blanket_taken"), true);
		updateAll();
	}
}

void LocationRVBlanket::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_blanket_taken")))
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

void LocationRVBlanket::clickAction2()
{
}

void LocationRVBlanket::clickAction0()
{
}

void LocationRVBlanket::whatOnClick0()
{
}

void LocationRVBlanket::whatOnClick()
{
}
