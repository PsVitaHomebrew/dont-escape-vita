#include "../game_all.h"

void RoofBird::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("deadbird");
	range = 5.0f;
	teleport = false;
	updateState();
}

void RoofBird::Update()
{
}

void RoofBird::whatOnClick()
{
}

void RoofBird::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("deadbird"))))
	{
		GameDataController::gd->setObjective(S("deadbird_taken"), true);
		updateAll();
	}
}

void RoofBird::updateState()
{
	if (GameDataController::gd->getObjective(S("chimney_cleaned")) && !GameDataController::gd->getObjective(S("deadbird_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void RoofBird::clickAction2()
{
}

void RoofBird::clickAction0()
{
}
