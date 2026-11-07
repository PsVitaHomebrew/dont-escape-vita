#include "../game_all.h"

void BarnPipeToPick::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pipe_to_pick");
	shined = false;
}

void BarnPipeToPick::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pipe"))))
	{
		GameDataController::gd->setObjective(S("barn_pipe_taken"), true);
		updateAll();
	}
}

void BarnPipeToPick::updateState()
{
	if (GameDataController::gd->getObjective(S("barn_pipe_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void BarnPipeToPick::clickAction2()
{
}

void BarnPipeToPick::clickAction0()
{
}
