#include "../game_all.h"

void HouseBSheet::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_sheet");
}

void HouseBSheet::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_sheet_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sheet"))))
	{
		GameDataController::gd->setObjective(S("house_b_sheet_taken"), true);
		updateState();
	}
}

void HouseBSheet::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("house_b_sheet_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	colliderManager->setCollider(-1);
}

void HouseBSheet::clickAction2()
{
}

void HouseBSheet::clickAction0()
{
}
