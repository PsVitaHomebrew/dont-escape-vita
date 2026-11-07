#include "../game_all.h"

void HouseBCoat2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_coat");
}

void HouseBCoat2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_coat2_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("coat2"))))
	{
		GameDataController::gd->setObjective(S("house_b_coat2_taken"), true);
		updateState();
	}
}

void HouseBCoat2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("house_b_closet_open")) && !GameDataController::gd->getObjective(S("house_b_coat2_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	colliderManager->setCollider(-1);
}

void HouseBCoat2::clickAction2()
{
}

void HouseBCoat2::clickAction0()
{
}
