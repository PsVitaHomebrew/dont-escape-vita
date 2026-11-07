#include "../game_all.h"

void Moonbase3Card::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon_card");
	updateAll();
}

void Moonbase3Card::clickAction()
{
	if (!GameDataController::gd->getObjective(S("moon_card_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("moon_card"))))
	{
		GameDataController::gd->setObjective(S("moon_card_taken"), true);
		updateState();
	}
}

void Moonbase3Card::updateState()
{
	if (!GameDataController::gd->getObjective(S("moon_card_taken")))
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

void Moonbase3Card::clickAction2()
{
}

void Moonbase3Card::clickAction0()
{
}
