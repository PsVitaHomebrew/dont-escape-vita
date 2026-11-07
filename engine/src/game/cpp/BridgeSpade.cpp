#include "../game_all.h"

void BridgeSpade::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("pull_w");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bridge_spade");
	range = 1.0f;
}

void BridgeSpade::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wood_snap);
	GameDataController::gd->setObjective(S("bridge_handle_taken"), true);
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("hammer_handle")), true);
}

void BridgeSpade::updateState()
{
	if (GameDataController::gd->getObjective(S("bridge_handle_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void BridgeSpade::clickAction2()
{
	updateAll();
}

void BridgeSpade::clickAction0()
{
}
