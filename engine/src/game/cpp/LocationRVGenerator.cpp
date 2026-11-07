#include "../game_all.h"

void LocationRVGenerator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_generator");
	range = 1.0f;
}

void LocationRVGenerator::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("generator"))))
	{
		GameDataController::gd->setObjective(S("rv_generator_taken"), true);
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_generator_taken")));
	}
}

void LocationRVGenerator::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_generator_taken")))
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

void LocationRVGenerator::clickAction2()
{
}

void LocationRVGenerator::clickAction0()
{
}

void LocationRVGenerator::whatOnClick0()
{
}

void LocationRVGenerator::whatOnClick()
{
}
