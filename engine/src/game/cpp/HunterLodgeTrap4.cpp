#include "../game_all.h"

void HunterLodgeTrap4::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("hunters_trap4");
	range = 2.0f;
	updateState();
}

void HunterLodgeTrap4::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_trap4_taken")))
	{
		pickItUp(nullptr);
	}
}

void HunterLodgeTrap4::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bear_trap_4"))))
	{
		GameDataController::gd->setObjective(S("hunters_lodge_trap4_taken"), true);
		updateAll();
	}
}

void HunterLodgeTrap4::whatOnClick()
{
}

void HunterLodgeTrap4::updateState()
{
	if (GameDataController::gd->getObjective(S("hunters_lodge_trap4_taken")) || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void HunterLodgeTrap4::clickAction2()
{
}

void HunterLodgeTrap4::clickAction0()
{
}
