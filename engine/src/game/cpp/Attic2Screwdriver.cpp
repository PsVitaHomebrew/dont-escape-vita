#include "../game_all.h"

void Attic2Screwdriver::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("screwdriver");
	range = 1.0f;
	updateState();
}

void Attic2Screwdriver::clickAction()
{
	pickItUp(nullptr);
}

void Attic2Screwdriver::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("screwdriver"))))
	{
		GameDataController::gd->setObjective(S("screwdriver_taken"), true);
		updateState();
	}
}

void Attic2Screwdriver::whatOnClick()
{
}

void Attic2Screwdriver::updateState()
{
	if (GameDataController::gd->getObjective(S("screwdriver_taken")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void Attic2Screwdriver::clickAction2()
{
}

void Attic2Screwdriver::clickAction0()
{
}
