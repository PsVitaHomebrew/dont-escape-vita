#include "../game_all.h"

void HouseBShovel::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_shovel");
	range = 1.0f;
}

void HouseBShovel::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_shovel_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("shovel"))))
	{
		GameDataController::gd->setObjective(S("house_b_shovel_taken"), true);
		updateState();
	}
}

void HouseBShovel::updateState()
{
	if (GameDataController::gd->getObjective(S("house_b_garage_open")))
	{
		if (GameDataController::gd->getObjective(S("house_b_shovel_taken")))
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
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		setCollider(-1);
	}
}

void HouseBShovel::clickAction2()
{
}

void HouseBShovel::clickAction0()
{
}
