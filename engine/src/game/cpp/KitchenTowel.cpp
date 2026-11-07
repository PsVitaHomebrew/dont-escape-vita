#include "../game_all.h"

void KitchenTowel::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_towel");
	range = 6.0f;
	updateState();
}

void KitchenTowel::clickAction()
{
	pickItUp(nullptr);
}

void KitchenTowel::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_1"))))
	{
		GameDataController::gd->setObjective(S("towel_1_taken"), true);
		updateState();
	}
}

void KitchenTowel::whatOnClick()
{
}

void KitchenTowel::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1 || GameDataController::gd->getObjective(S("towel_1_taken")))
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

void KitchenTowel::clickAction2()
{
}

void KitchenTowel::clickAction0()
{
}
