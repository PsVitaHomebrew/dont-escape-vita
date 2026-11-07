#include "../game_all.h"

void BarnShortPipe::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("short_pipe");
}

void BarnShortPipe::clickAction()
{
	if (GameDataController::gd->getObjective(S("barn_pipe_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pipe"))))
	{
		GameDataController::gd->setObjective(S("barn_pipe_taken"), true);
		updateState();
	}
}

void BarnShortPipe::updateState()
{
	if (!GameDataController::gd->getObjective(S("barn_pipe_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void BarnShortPipe::clickAction2()
{
}

void BarnShortPipe::clickAction0()
{
}
