#include "../game_all.h"

void HouseBBlanket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_blanket");
}

void HouseBBlanket::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_blanket_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("blanketb"))))
	{
		GameDataController::gd->setObjective(S("house_b_blanket_taken"), true);
		updateState();
	}
}

void HouseBBlanket::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("house_b_blanket_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	colliderManager->setCollider(-1);
}

void HouseBBlanket::clickAction2()
{
}

void HouseBBlanket::clickAction0()
{
}
