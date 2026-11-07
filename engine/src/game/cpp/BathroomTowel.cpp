#include "../game_all.h"

void BathroomTowel::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bathroom_towel");
	range = 6.0f;
	updateState();
}

void BathroomTowel::clickAction()
{
	pickItUp(nullptr);
}

void BathroomTowel::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("towel_2"))))
	{
		GameDataController::gd->setObjective(S("towel_2_taken"), true);
		updateState();
	}
}

void BathroomTowel::whatOnClick()
{
}

void BathroomTowel::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1 || GameDataController::gd->getObjective(S("towel_2_taken")))
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

void BathroomTowel::clickAction2()
{
}

void BathroomTowel::clickAction0()
{
}
