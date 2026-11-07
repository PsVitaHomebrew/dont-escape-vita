#include "../game_all.h"

void AtticExtCord::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ext_cord");
	range = 1.0f;
	updateState();
}

void AtticExtCord::clickAction()
{
	pickItUp(nullptr);
}

void AtticExtCord::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("ext_cord"))))
	{
		GameDataController::gd->setObjective(S("ext_cord_taken"), true);
		updateState();
	}
}

void AtticExtCord::whatOnClick()
{
}

void AtticExtCord::updateState()
{
	if (GameDataController::gd->getObjective(S("ext_cord_taken")))
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

void AtticExtCord::clickAction2()
{
}

void AtticExtCord::clickAction0()
{
}
