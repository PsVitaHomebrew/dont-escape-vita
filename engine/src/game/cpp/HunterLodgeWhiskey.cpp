#include "../game_all.h"

void HunterLodgeWhiskey::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("hunters_whiskey");
	range = 2.0f;
	updateState();
}

void HunterLodgeWhiskey::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_whiskey_taken")))
	{
		pickItUp(nullptr);
	}
}

void HunterLodgeWhiskey::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("whiskey"))))
	{
		GameDataController::gd->setObjective(S("hunters_lodge_whiskey_taken"), true);
		updateAll();
	}
}

void HunterLodgeWhiskey::whatOnClick()
{
}

void HunterLodgeWhiskey::updateState()
{
	if (GameDataController::gd->getObjective(S("hunters_lodge_whiskey_taken")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void HunterLodgeWhiskey::clickAction2()
{
}

void HunterLodgeWhiskey::clickAction0()
{
}
