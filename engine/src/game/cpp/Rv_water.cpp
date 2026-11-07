#include "../game_all.h"

void Rv_water::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_water2");
	range = 1.0f;
}

void Rv_water::clickAction()
{
	if (!GameDataController::gd->getObjective(S("rv_water3_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("water3"))))
		{
			GameDataController::gd->setObjective(S("rv_water3_taken"), true);
			updateAll();
		}
	}
	else if (!GameDataController::gd->getObjective(S("rv_water4_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("water4"))))
	{
		GameDataController::gd->setObjective(S("rv_water4_taken"), true);
		updateAll();
	}
}

void Rv_water::updateState()
{
	if (!GameDataController::gd->getObjective(S("rv_water3_taken")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_sprite(ww2);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("action_n");
		objectName = S("rv_water1");
	}
	else if (!GameDataController::gd->getObjective(S("rv_water4_taken")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_sprite(ww1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("action_n");
		objectName = S("rv_water2");
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_sprite(ww2);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Rv_water::clickAction2()
{
}

void Rv_water::clickAction0()
{
}
