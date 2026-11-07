#include "../game_all.h"

void HuntersScope::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("hunters_scope");
	range = 2.0f;
	updateState();
}

void HuntersScope::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_scope_taken")))
	{
		pickItUp(nullptr);
	}
}

void HuntersScope::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("scope"))))
	{
		GameDataController::gd->setObjective(S("hunters_lodge_scope_taken"), true);
		updateAll();
	}
}

void HuntersScope::whatOnClick()
{
}

void HuntersScope::updateState()
{
	if (GameDataController::gd->getObjective(S("hunters_lodge_scope_taken")) || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0)
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

void HuntersScope::clickAction2()
{
}

void HuntersScope::clickAction0()
{
}
