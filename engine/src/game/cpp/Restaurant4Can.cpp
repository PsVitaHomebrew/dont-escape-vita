#include "../game_all.h"

void Restaurant4Can::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_can");
	range = 1.0f;
}

void Restaurant4Can::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_can_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("foodcan"))))
	{
		GameDataController::gd->setObjective(S("restaurant_can_taken"), true);
		updateState();
	}
}

void Restaurant4Can::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_can_taken")))
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

void Restaurant4Can::clickAction2()
{
}

void Restaurant4Can::clickAction0()
{
}
